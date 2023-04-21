using System;
using System.Data;
using System.Data.SqlClient;
using System.Windows.Forms;
using System.Configuration;

namespace Lab2
{
    public partial class Form1 : Form
    {
        private readonly DataSet _dataSet = new DataSet();
        private SqlConnection _connection;

        private SqlDataAdapter _adapterParent, _adapterChild;
        private readonly BindingSource _bindingSourceParent = new BindingSource();
        private readonly BindingSource _bindingSourceChild = new BindingSource();

        private void InitDatabase()
        {
            String connectionString = ConfigurationManager.ConnectionStrings["ConnectionString"].ConnectionString;
            String database = ConfigurationManager.AppSettings["Database"];

            this._connection = new SqlConnection(String.Format(connectionString, database));
            this._adapterParent = new SqlDataAdapter(ConfigurationManager.AppSettings["SelectParent"], this._connection);
            this._adapterChild = new SqlDataAdapter(ConfigurationManager.AppSettings["SelectChild"], this._connection);

            new SqlCommandBuilder(this._adapterChild);
            new SqlCommandBuilder(this._adapterParent).GetInsertCommand();

            this._adapterParent.Fill(this._dataSet, ConfigurationManager.AppSettings["ParentTableName"]);
            this._adapterChild.Fill(this._dataSet, ConfigurationManager.AppSettings["ChildTableName"]);

            DataColumn parentDataColumn = this._dataSet.Tables[ConfigurationManager.AppSettings["ParentTableName"]].Columns[ConfigurationManager.AppSettings["ParentReferencedKey"]];
            DataColumn childDataColumn = this._dataSet.Tables[ConfigurationManager.AppSettings["ChildTableName"]].Columns[ConfigurationManager.AppSettings["ChildForeignKey"]];

            String relationName = ConfigurationManager.AppSettings["ForeignKey"];

            var dataRelation = new DataRelation(
                relationName,
                parentDataColumn,
                childDataColumn
            );

            this._dataSet.Relations.Add( dataRelation );
        }

        private void InitializeUI()
        {
            _bindingSourceParent.DataSource = _dataSet;
            _bindingSourceParent.DataMember = ConfigurationManager.AppSettings["ParentTableName"];

            _bindingSourceChild.DataSource = _bindingSourceParent;
            _bindingSourceChild.DataMember = ConfigurationManager.AppSettings["ForeignKey"];

            dataGridParent.DataSource = _bindingSourceParent;
            dataGridChild.DataSource = _bindingSourceChild;
        }

        public Form1()
        {
            InitializeComponent();
        }

        private void groupListBindingNavigatorSaveItem_Click(object sender, EventArgs e)
        {
            this.Validate();
            this.groupListBindingSource.EndEdit();
            this.tableAdapterManager.UpdateAll(this.dbmsDataSet);

        }

        private void refreshButton_Click(object sender, EventArgs e)
        {
            _dataSet.Tables[ConfigurationManager.AppSettings["ChildTableName"]].Clear();
            _dataSet.Tables[ConfigurationManager.AppSettings["ParentTableName"]].Clear();
            _adapterParent.Fill(_dataSet, ConfigurationManager.AppSettings["ParentTableName"]);
            _adapterChild.Fill(_dataSet, ConfigurationManager.AppSettings["ChildTableName"]);
        }

        private void updateButton_Click(object sender, EventArgs e)
        {
            _adapterChild.Update(_dataSet, ConfigurationManager.AppSettings["ChildTableName"]);
            _adapterParent.Update(_dataSet, ConfigurationManager.AppSettings["ParentTableName"]);
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            // TODO: This line of code loads data into the 'dbmsDataSet.GroupList' table. You can move, or remove it, as needed.
            this.groupListTableAdapter.Fill(this.dbmsDataSet.GroupList);
            InitDatabase();
            InitializeUI();

            // TODO: This line of code loads data into the 'dbmsDataSet.Account' table. You can move, or remove it, as needed.
            //this.accountTableAdapter.Fill(this._dataSet.Account);
            // TODO: This line of code loads data into the 'dbmsDataSet.Login' table. You can move, or remove it, as needed.
            //this.loginTableAdapter.Fill(this._dataSet.Login);

        }
    }
}
