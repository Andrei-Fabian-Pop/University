using System;
using System.Data;
using System.Data.SqlClient;
using System.Windows.Forms;

namespace WindowsFormsApp1
{
    public partial class Form1 : Form
    {
        private int _accountId = -1;
        private int _loginId = -1;
        private const string DatabaseConnection = "Data Source=DESKTOP-L6427T1;Initial Catalog=dbms;Integrated Security=True";
        public Form1()
        {
            InitializeComponent();
            PopulateLogin();
        }

        private void ClearData()
        {
            textBox_id.Clear();
            textBox_lastn.Clear();
            textBox_email.Clear();
            textBox_middlen.Clear();
        }

        public void PopulateAccount()
        {
            var connect = new SqlConnection(DatabaseConnection);
            connect.Open();
            var cmd = new SqlCommand("select * from Account", connect);
            var dataTable = new DataTable();
            var adapter = new SqlDataAdapter(cmd);
            adapter.Fill(dataTable);
            dataGridView_account.DataSource = dataTable;
            dataGridView_account.ReadOnly = true;
            cmd.ExecuteNonQuery();
            connect.Close();
        }

        private void PopulateLogin()
        {
            var connect = new SqlConnection(DatabaseConnection);
            connect.Open();
            var cmd = new SqlCommand("select * from [Login]", connect);
            // cmd.Parameters.AddWithValue("@id", loginId);
            var dt = new DataTable();
            var adapter = new SqlDataAdapter(cmd);
            adapter.Fill(dt);
            dataGridView_login.DataSource = dt;
            dataGridView_login.ReadOnly = true;
            cmd.ExecuteNonQuery();
            connect.Close();
        }

        private void dataGridView_login_CellClick(object sender, DataGridViewCellEventArgs e)
        {
            ClearData();
            dataGridView_login.CurrentRow.Selected = true;
            _loginId = int.Parse(dataGridView_login.Rows[e.RowIndex].Cells["id"].Value.ToString());
            textBox_id.Text = _loginId.ToString();
            if (dataGridView_login.SelectedRows.Count > 0)
            {
                groupBox1.Enabled = true;
            }

            var connect = new SqlConnection(DatabaseConnection);
            connect.Open();
            var cmd = new SqlCommand("select * from Account where login=@id", connect);
            cmd.Parameters.AddWithValue("@id", _loginId);
            var dt = new DataTable();
            var adapter = new SqlDataAdapter(cmd);
            adapter.Fill(dt);
            dataGridView_account.DataSource = dt;
            dataGridView_account.ReadOnly = true;
            cmd.ExecuteNonQuery();
            connect.Close();
        }

        private void dataGridView_account_CellClick(object sender, DataGridViewCellEventArgs e) 
        {
            ClearData();
            _accountId = int.Parse(dataGridView_account.Rows[e.RowIndex].Cells["id"].Value.ToString());
            textBox_id.Text = dataGridView_account.Rows[e.RowIndex].Cells["id"].Value.ToString();
            textBox_email.Text = dataGridView_account.Rows[e.RowIndex].Cells["email"].Value.ToString();
            textBox_firstn.Text = dataGridView_account.Rows[e.RowIndex].Cells["firstName"].Value.ToString();
            textBox_middlen.Text = dataGridView_account.Rows[e.RowIndex].Cells["middleName"].Value.ToString();
            textBox_lastn.Text = dataGridView_account.Rows[e.RowIndex].Cells["lastName"].Value.ToString();
            textBox_mobile.Text = dataGridView_account.Rows[e.RowIndex].Cells["mobile"].Value.ToString();
            textBox_fax.Text = dataGridView_account.Rows[e.RowIndex].Cells["fax"].Value.ToString();
            textBox_address.Text = dataGridView_account.Rows[e.RowIndex].Cells["address"].Value.ToString();
            textBox_createdat.Text = dataGridView_account.Rows[e.RowIndex].Cells["createdAt"].Value.ToString();
        }

        private void button_add_Click(object sender, EventArgs e)
        {
            var connect = new SqlConnection(DatabaseConnection);
            connect.Open();
            var cmd = new SqlCommand("insert into Account values (@email, @firstName, @middleName, @lastName, @mobile, @fax, @address, @createdAt, @login)", connect);
            cmd.Parameters.AddWithValue("@email", textBox_email.Text);
            cmd.Parameters.AddWithValue("@firstName", textBox_firstn.Text);
            cmd.Parameters.AddWithValue("@middleName", textBox_middlen.Text);
            cmd.Parameters.AddWithValue("@lastName", textBox_lastn.Text);
            cmd.Parameters.AddWithValue("@mobile", textBox_mobile.Text);
            cmd.Parameters.AddWithValue("@fax", textBox_fax.Text);
            cmd.Parameters.AddWithValue("@address", textBox_address.Text);
            cmd.Parameters.AddWithValue("@createdAt", textBox_createdat.Text);
            cmd.Parameters.AddWithValue("@login", _loginId.ToString());
            cmd.ExecuteNonQuery();
            ClearData();
            PopulateLogin();
            connect.Close();
            MessageBox.Show("Successfully Inserted");
        }

        private void button_update_Click(object sender, EventArgs e)
        {
            var connect = new SqlConnection(DatabaseConnection);
            connect.Open();
            var cmd = new SqlCommand("update Account set email=@email where id=@accountId", connect);
            cmd.Parameters.AddWithValue("@accountId", _accountId);
            cmd.Parameters.AddWithValue("@email", textBox_email.Text);
            cmd.ExecuteNonQuery();
            ClearData();
            PopulateLogin();
            connect.Close();
            MessageBox.Show("Successfully Inserted");
        }

        private void button_delete_Click(object sender, EventArgs e)
        {
            var connect = new SqlConnection(DatabaseConnection);
            connect.Open();
            var cmd = new SqlCommand("delete from Account where id=@accountId", connect);
            cmd.Parameters.AddWithValue("@accountId", _accountId);
            cmd.ExecuteNonQuery();
            ClearData();
            PopulateLogin();
            connect.Close();
            MessageBox.Show("Successfully Deleted");
        }
    }
}