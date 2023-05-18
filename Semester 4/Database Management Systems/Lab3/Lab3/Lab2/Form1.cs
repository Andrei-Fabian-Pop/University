using System;
using System.Data;
using System.Data.SqlClient;
using System.Windows.Forms;
using System.Configuration;
using System.Threading;

namespace Lab3
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

        private void inserWithRolback_button_Click(object sender, EventArgs e)
        {
            using (SqlConnection connection = new SqlConnection(ConfigurationManager.ConnectionStrings["ConnectionString"].ConnectionString))
            {
                connection.Open();

                SqlTransaction transaction = connection.BeginTransaction();

                try
                {
                    SqlCommand command1 = new SqlCommand("INSERT INTO Table1 (Address) VALUES (@Value1)", connection, transaction);
                    command1.Parameters.AddWithValue("@Value1", "\"hjdagj\", \"hgjdsga\", \"jh\", \"ds\", \"+40696969696\", 0, 1, \"2012-06-18 10:34:00.000\", 1");
                    command1.ExecuteNonQuery();

                    SqlCommand command2 = new SqlCommand("INSERT INTO Table2 (Account) VALUES (@Value2)", connection, transaction);
                    command2.Parameters.AddWithValue("@Value2", "\"Romania\", \"Nono\", \"nono\", \"noo\", 11, \"45865\"");
                    command2.ExecuteNonQuery();

                    transaction.Commit();
                }
                catch (Exception exception)
                {
                    transaction.Rollback();
                    Console.WriteLine(exception.ToString());
                }
            }
        }

        private void dirtyRead(object sender, EventArgs e)
        {
            using (SqlConnection connection = new SqlConnection(ConfigurationManager.ConnectionStrings["ConnectionString"].ConnectionString))
            {
                connection.Open();
                using (SqlTransaction transactionA = connection.BeginTransaction(IsolationLevel.ReadCommitted))
                {
                    try
                    {
                        Thread.Sleep(5000);
                        transactionA.Commit();
                    }
                    catch (Exception ex)
                    {
                        transactionA.Rollback();
                    }
                }

                using (SqlTransaction transactionB = connection.BeginTransaction(IsolationLevel.ReadUncommitted))
                {
                    try
                    {
                        transactionB.Commit();
                    }
                    catch (Exception ex)
                    {
                        transactionB.Rollback();
                    }
                }
            }
        }

        private void nonRepeatableRead(object sender, EventArgs e)
        {
            using (SqlConnection connection = new SqlConnection(ConfigurationManager.ConnectionStrings["ConnectionString"].ConnectionString))
            {
                connection.Open();
                using (SqlTransaction transactionA = connection.BeginTransaction(IsolationLevel.ReadCommitted))
                {
                    try
                    {
                        Thread.Sleep(5000);
                        transactionA.Commit();
                    }
                    catch (Exception ex)
                    {
                        transactionA.Rollback();
                    }
                }

                using (SqlTransaction transactionB = connection.BeginTransaction(IsolationLevel.ReadCommitted))
                {
                    try
                    {
                        transactionB.Commit();
                    }
                    catch (Exception ex)
                    {
                        transactionB.Rollback();
                    }
                }
            }
        }

        private void phantomRead(object sender, EventArgs e)
        {
            using (SqlConnection connection = new SqlConnection(ConfigurationManager.ConnectionStrings["ConnectionString"].ConnectionString))
            {
                connection.Open();
                using (SqlTransaction transactionA = connection.BeginTransaction(IsolationLevel.ReadCommitted))
                {
                    try
                    {
                        Thread.Sleep(5000);
                        transactionA.Commit();
                    }
                    catch (Exception ex)
                    {
                        transactionA.Rollback();
                    }
                }

                using (SqlTransaction transactionB = connection.BeginTransaction(IsolationLevel.ReadCommitted))
                {
                    try
                    {
                        transactionB.Commit();
                    }
                    catch (Exception ex)
                    {
                        transactionB.Rollback();
                    }
                }
            }
        }

        private void deadlock(object sender, EventArgs e)
        {
            using (SqlConnection connection = new SqlConnection(ConfigurationManager.ConnectionStrings["ConnectionString"].ConnectionString))
            {
                connection.Open();
                using (SqlTransaction transactionA = connection.BeginTransaction(IsolationLevel.Serializable))
                {
                    try
                    {
                        Thread.Sleep(2000);
                        transactionA.Commit();
                    }
                    catch (Exception ex)
                    {
                        transactionA.Rollback();
                    }
                }

                using (SqlTransaction transactionB = connection.BeginTransaction(IsolationLevel.Serializable))
                {
                    try
                    {
                        Thread.Sleep(2000);
                        transactionB.Commit();
                    }
                    catch (Exception ex)
                    {
                        transactionB.Rollback();
                    }
                }
            }

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
