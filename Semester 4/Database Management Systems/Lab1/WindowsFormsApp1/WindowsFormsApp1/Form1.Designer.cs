namespace WindowsFormsApp1
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
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
            this.dataGridView_account = new System.Windows.Forms.DataGridView();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.textBox_id = new System.Windows.Forms.TextBox();
            this.textBox_lastn = new System.Windows.Forms.TextBox();
            this.textBox_middlen = new System.Windows.Forms.TextBox();
            this.textBox_email = new System.Windows.Forms.TextBox();
            this.button_add = new System.Windows.Forms.Button();
            this.button_delete = new System.Windows.Forms.Button();
            this.button_update = new System.Windows.Forms.Button();
            this.dataGridView_login = new System.Windows.Forms.DataGridView();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.textBox_firstn = new System.Windows.Forms.TextBox();
            this.label9 = new System.Windows.Forms.Label();
            this.textBox_createdat = new System.Windows.Forms.TextBox();
            this.textBox_address = new System.Windows.Forms.TextBox();
            this.textBox_mobile = new System.Windows.Forms.TextBox();
            this.textBox_fax = new System.Windows.Forms.TextBox();
            this.label8 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView_account)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView_login)).BeginInit();
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // dataGridView_account
            // 
            this.dataGridView_account.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridView_account.Location = new System.Drawing.Point(68, 309);
            this.dataGridView_account.Name = "dataGridView_account";
            this.dataGridView_account.Size = new System.Drawing.Size(676, 198);
            this.dataGridView_account.TabIndex = 1;
            this.dataGridView_account.CellClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.dataGridView_account_CellClick);
            // 
            // label1
            // 
            this.label1.Location = new System.Drawing.Point(48, 18);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(100, 23);
            this.label1.TabIndex = 2;
            this.label1.Text = "id";
            // 
            // label2
            // 
            this.label2.Location = new System.Drawing.Point(48, 41);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(100, 23);
            this.label2.TabIndex = 3;
            this.label2.Text = "email";
            // 
            // label3
            // 
            this.label3.Location = new System.Drawing.Point(48, 115);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(100, 23);
            this.label3.TabIndex = 4;
            this.label3.Text = "Last Name";
            // 
            // label4
            // 
            this.label4.Location = new System.Drawing.Point(48, 92);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(100, 23);
            this.label4.TabIndex = 5;
            this.label4.Text = "Middle Name";
            // 
            // textBox_id
            // 
            this.textBox_id.Location = new System.Drawing.Point(184, 18);
            this.textBox_id.Name = "textBox_id";
            this.textBox_id.ReadOnly = true;
            this.textBox_id.Size = new System.Drawing.Size(100, 20);
            this.textBox_id.TabIndex = 6;
            // 
            // textBox_lastn
            // 
            this.textBox_lastn.Location = new System.Drawing.Point(184, 111);
            this.textBox_lastn.Name = "textBox_lastn";
            this.textBox_lastn.Size = new System.Drawing.Size(100, 20);
            this.textBox_lastn.TabIndex = 7;
            // 
            // textBox_middlen
            // 
            this.textBox_middlen.Location = new System.Drawing.Point(184, 85);
            this.textBox_middlen.Name = "textBox_middlen";
            this.textBox_middlen.Size = new System.Drawing.Size(100, 20);
            this.textBox_middlen.TabIndex = 8;
            // 
            // textBox_email
            // 
            this.textBox_email.Location = new System.Drawing.Point(184, 38);
            this.textBox_email.Name = "textBox_email";
            this.textBox_email.Size = new System.Drawing.Size(100, 20);
            this.textBox_email.TabIndex = 9;
            // 
            // button_add
            // 
            this.button_add.Location = new System.Drawing.Point(533, 25);
            this.button_add.Name = "button_add";
            this.button_add.Size = new System.Drawing.Size(75, 23);
            this.button_add.TabIndex = 10;
            this.button_add.Text = "ADD";
            this.button_add.UseVisualStyleBackColor = true;
            this.button_add.Click += new System.EventHandler(this.button_add_Click);
            // 
            // button_delete
            // 
            this.button_delete.Location = new System.Drawing.Point(533, 87);
            this.button_delete.Name = "button_delete";
            this.button_delete.Size = new System.Drawing.Size(75, 23);
            this.button_delete.TabIndex = 11;
            this.button_delete.Text = "DELETE";
            this.button_delete.UseVisualStyleBackColor = true;
            this.button_delete.Click += new System.EventHandler(this.button_delete_Click);
            // 
            // button_update
            // 
            this.button_update.Location = new System.Drawing.Point(533, 54);
            this.button_update.Name = "button_update";
            this.button_update.Size = new System.Drawing.Size(75, 23);
            this.button_update.TabIndex = 12;
            this.button_update.Text = "UPDATE";
            this.button_update.UseVisualStyleBackColor = true;
            this.button_update.Click += new System.EventHandler(this.button_update_Click);
            // 
            // dataGridView_login
            // 
            this.dataGridView_login.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridView_login.Location = new System.Drawing.Point(64, 56);
            this.dataGridView_login.Name = "dataGridView_login";
            this.dataGridView_login.Size = new System.Drawing.Size(680, 195);
            this.dataGridView_login.TabIndex = 13;
            this.dataGridView_login.CellClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.dataGridView_login_CellClick);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.textBox_firstn);
            this.groupBox1.Controls.Add(this.label9);
            this.groupBox1.Controls.Add(this.textBox_createdat);
            this.groupBox1.Controls.Add(this.textBox_address);
            this.groupBox1.Controls.Add(this.textBox_mobile);
            this.groupBox1.Controls.Add(this.textBox_fax);
            this.groupBox1.Controls.Add(this.label8);
            this.groupBox1.Controls.Add(this.label7);
            this.groupBox1.Controls.Add(this.label6);
            this.groupBox1.Controls.Add(this.label5);
            this.groupBox1.Controls.Add(this.button_update);
            this.groupBox1.Controls.Add(this.button_delete);
            this.groupBox1.Controls.Add(this.button_add);
            this.groupBox1.Controls.Add(this.textBox_email);
            this.groupBox1.Controls.Add(this.textBox_middlen);
            this.groupBox1.Controls.Add(this.textBox_lastn);
            this.groupBox1.Controls.Add(this.textBox_id);
            this.groupBox1.Controls.Add(this.label4);
            this.groupBox1.Controls.Add(this.label3);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Enabled = false;
            this.groupBox1.Location = new System.Drawing.Point(20, 530);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(683, 245);
            this.groupBox1.TabIndex = 14;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "groupBox1";
            // 
            // textBox_firstn
            // 
            this.textBox_firstn.Location = new System.Drawing.Point(184, 64);
            this.textBox_firstn.Name = "textBox_firstn";
            this.textBox_firstn.Size = new System.Drawing.Size(100, 20);
            this.textBox_firstn.TabIndex = 22;
            // 
            // label9
            // 
            this.label9.Location = new System.Drawing.Point(48, 67);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(100, 23);
            this.label9.TabIndex = 21;
            this.label9.Text = "First Name";
            // 
            // textBox_createdat
            // 
            this.textBox_createdat.Location = new System.Drawing.Point(184, 210);
            this.textBox_createdat.Name = "textBox_createdat";
            this.textBox_createdat.Size = new System.Drawing.Size(100, 20);
            this.textBox_createdat.TabIndex = 20;
            // 
            // textBox_address
            // 
            this.textBox_address.Location = new System.Drawing.Point(184, 184);
            this.textBox_address.Name = "textBox_address";
            this.textBox_address.Size = new System.Drawing.Size(100, 20);
            this.textBox_address.TabIndex = 19;
            // 
            // textBox_mobile
            // 
            this.textBox_mobile.Location = new System.Drawing.Point(184, 135);
            this.textBox_mobile.Name = "textBox_mobile";
            this.textBox_mobile.Size = new System.Drawing.Size(100, 20);
            this.textBox_mobile.TabIndex = 18;
            // 
            // textBox_fax
            // 
            this.textBox_fax.Location = new System.Drawing.Point(184, 158);
            this.textBox_fax.Name = "textBox_fax";
            this.textBox_fax.Size = new System.Drawing.Size(100, 20);
            this.textBox_fax.TabIndex = 17;
            // 
            // label8
            // 
            this.label8.Location = new System.Drawing.Point(48, 207);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(100, 23);
            this.label8.TabIndex = 16;
            this.label8.Text = "Created At";
            // 
            // label7
            // 
            this.label7.Location = new System.Drawing.Point(48, 184);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(100, 23);
            this.label7.TabIndex = 15;
            this.label7.Text = "Address";
            // 
            // label6
            // 
            this.label6.Location = new System.Drawing.Point(48, 161);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(100, 23);
            this.label6.TabIndex = 14;
            this.label6.Text = "Fax";
            // 
            // label5
            // 
            this.label5.Location = new System.Drawing.Point(48, 138);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(100, 23);
            this.label5.TabIndex = 13;
            this.label5.Text = "Mobile";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(821, 787);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.dataGridView_login);
            this.Controls.Add(this.dataGridView_account);
            this.Name = "Form1";
            this.Text = "Form1";
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView_account)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView_login)).EndInit();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.ResumeLayout(false);
        }

        private System.Windows.Forms.TextBox textBox_firstn;
        private System.Windows.Forms.Label label9;

        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.TextBox textBox_fax;
        private System.Windows.Forms.TextBox textBox_mobile;
        private System.Windows.Forms.TextBox textBox_address;
        private System.Windows.Forms.TextBox textBox_createdat;

        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label7;

        private System.Windows.Forms.Label label5;

        private System.Windows.Forms.GroupBox groupBox1;

        private System.Windows.Forms.DataGridView dataGridView_account;

        private System.Windows.Forms.Button button_add;
        private System.Windows.Forms.Button button_delete;
        private System.Windows.Forms.Button button_update;

        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox textBox_id;
        private System.Windows.Forms.TextBox textBox_lastn;
        private System.Windows.Forms.TextBox textBox_middlen;
        private System.Windows.Forms.TextBox textBox_email;

        private System.Windows.Forms.Label label2;

        private System.Windows.Forms.Label label1;

        private System.Windows.Forms.DataGridView dataGridView_login;

        #endregion
    }
}