namespace Lab2
{
    partial class Form1
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.dbmsDataSet = new Lab2.dbmsDataSet();
            this.groupListBindingSource = new System.Windows.Forms.BindingSource(this.components);
            this.groupListTableAdapter = new Lab2.dbmsDataSetTableAdapters.GroupListTableAdapter();
            this.tableAdapterManager = new Lab2.dbmsDataSetTableAdapters.TableAdapterManager();
            this.dataGridParent = new System.Windows.Forms.DataGridView();
            this.dataGridChild = new System.Windows.Forms.DataGridView();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.refreshButton = new System.Windows.Forms.Button();
            this.updateButton = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.dbmsDataSet)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.groupListBindingSource)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridParent)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridChild)).BeginInit();
            this.SuspendLayout();
            // 
            // dbmsDataSet
            // 
            this.dbmsDataSet.DataSetName = "dbmsDataSet";
            this.dbmsDataSet.Namespace = "http://tempuri.org/dbmsDataSet.xsd";
            this.dbmsDataSet.SchemaSerializationMode = System.Data.SchemaSerializationMode.IncludeSchema;
            // 
            // groupListBindingSource
            // 
            this.groupListBindingSource.DataMember = "GroupList";
            this.groupListBindingSource.DataSource = this.dbmsDataSet;
            // 
            // groupListTableAdapter
            // 
            this.groupListTableAdapter.ClearBeforeFill = true;
            // 
            // tableAdapterManager
            // 
            this.tableAdapterManager.AccountTableAdapter = null;
            this.tableAdapterManager.AddressTableAdapter = null;
            this.tableAdapterManager.BackupDataSetBeforeUpdate = false;
            this.tableAdapterManager.EmailTableAdapter = null;
            this.tableAdapterManager.GroupListTableAdapter = this.groupListTableAdapter;
            this.tableAdapterManager.GroupTableAdapter = null;
            this.tableAdapterManager.LoginTableAdapter = null;
            this.tableAdapterManager.ReminderTableAdapter = null;
            this.tableAdapterManager.SubscriptionTableAdapter = null;
            this.tableAdapterManager.UpdateOrder = Lab2.dbmsDataSetTableAdapters.TableAdapterManager.UpdateOrderOption.InsertUpdateDelete;
            this.tableAdapterManager.UserConversationTableAdapter = null;
            this.tableAdapterManager.UserTableAdapter = null;
            // 
            // dataGridParent
            // 
            this.dataGridParent.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.Fill;
            this.dataGridParent.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridParent.Location = new System.Drawing.Point(35, 35);
            this.dataGridParent.Name = "dataGridParent";
            this.dataGridParent.RowTemplate.Height = 25;
            this.dataGridParent.Size = new System.Drawing.Size(1112, 174);
            this.dataGridParent.TabIndex = 0;
            // 
            // dataGridChild
            // 
            this.dataGridChild.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.Fill;
            this.dataGridChild.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridChild.Location = new System.Drawing.Point(35, 249);
            this.dataGridChild.Name = "dataGridChild";
            this.dataGridChild.RowTemplate.Height = 25;
            this.dataGridChild.Size = new System.Drawing.Size(1112, 167);
            this.dataGridChild.TabIndex = 1;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(32, 224);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(60, 13);
            this.label1.TabIndex = 2;
            this.label1.Text = "Child Table";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(35, 10);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(68, 13);
            this.label2.TabIndex = 3;
            this.label2.Text = "Parent Table";
            // 
            // refreshButton
            // 
            this.refreshButton.Location = new System.Drawing.Point(38, 451);
            this.refreshButton.Name = "refreshButton";
            this.refreshButton.Size = new System.Drawing.Size(96, 23);
            this.refreshButton.TabIndex = 4;
            this.refreshButton.Text = "Refresh";
            this.refreshButton.UseVisualStyleBackColor = true;
            this.refreshButton.Click += new System.EventHandler(this.refreshButton_Click);
            // 
            // updateButton
            // 
            this.updateButton.Location = new System.Drawing.Point(147, 451);
            this.updateButton.Name = "updateButton";
            this.updateButton.Size = new System.Drawing.Size(96, 23);
            this.updateButton.TabIndex = 5;
            this.updateButton.Text = "Update";
            this.updateButton.UseVisualStyleBackColor = true;
            this.updateButton.Click += new System.EventHandler(this.updateButton_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1273, 763);
            this.Controls.Add(this.updateButton);
            this.Controls.Add(this.refreshButton);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.dataGridChild);
            this.Controls.Add(this.dataGridParent);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize)(this.dbmsDataSet)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.groupListBindingSource)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridParent)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridChild)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();
        }

        private System.Windows.Forms.Button refreshButton;
        private System.Windows.Forms.Button updateButton;

        #endregion
        private dbmsDataSet dbmsDataSet;
        private System.Windows.Forms.BindingSource groupListBindingSource;
        private dbmsDataSetTableAdapters.GroupListTableAdapter groupListTableAdapter;
        private dbmsDataSetTableAdapters.TableAdapterManager tableAdapterManager;
        private System.Windows.Forms.DataGridView dataGridParent;
        private System.Windows.Forms.DataGridView dataGridChild;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
    }
}
