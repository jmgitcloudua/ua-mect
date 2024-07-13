
namespace WinFormsApp2
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
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.btnHello = new System.Windows.Forms.Button();
            this.btnTest = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.txtServerBox = new System.Windows.Forms.TextBox();
            this.txtUserBox = new System.Windows.Forms.TextBox();
            this.textPasswordBox = new System.Windows.Forms.TextBox();
            this.SuspendLayout();
            // 
            // btnHello
            // 
            this.btnHello.Location = new System.Drawing.Point(462, 317);
            this.btnHello.Name = "btnHello";
            this.btnHello.Size = new System.Drawing.Size(207, 70);
            this.btnHello.TabIndex = 0;
            this.btnHello.Text = "Hello Table";
            this.btnHello.UseVisualStyleBackColor = true;
            this.btnHello.Click += new System.EventHandler(this.hello_click);
            // 
            // btnTest
            // 
            this.btnTest.Location = new System.Drawing.Point(181, 317);
            this.btnTest.Name = "btnTest";
            this.btnTest.Size = new System.Drawing.Size(213, 70);
            this.btnTest.TabIndex = 1;
            this.btnTest.Text = "Test Connection";
            this.btnTest.UseVisualStyleBackColor = true;
            this.btnTest.Click += new System.EventHandler(this.conn_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(110, 95);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(50, 20);
            this.label1.TabIndex = 2;
            this.label1.Text = "Server";
            this.label1.Click += new System.EventHandler(this.label1_Click);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(110, 168);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(38, 20);
            this.label2.TabIndex = 3;
            this.label2.Text = "User";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(90, 241);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(70, 20);
            this.label3.TabIndex = 4;
            this.label3.Text = "Password";
            // 
            // txtServerBox
            // 
            this.txtServerBox.Location = new System.Drawing.Point(283, 95);
            this.txtServerBox.Name = "txtServerBox";
            this.txtServerBox.Size = new System.Drawing.Size(386, 27);
            this.txtServerBox.TabIndex = 5;
            // 
            // txtUserBox
            // 
            this.txtUserBox.Location = new System.Drawing.Point(283, 168);
            this.txtUserBox.Name = "txtUserBox";
            this.txtUserBox.Size = new System.Drawing.Size(386, 27);
            this.txtUserBox.TabIndex = 6;
            // 
            // textPasswordBox
            // 
            this.textPasswordBox.Location = new System.Drawing.Point(283, 241);
            this.textPasswordBox.Name = "textPasswordBox";
            this.textPasswordBox.Size = new System.Drawing.Size(386, 27);
            this.textPasswordBox.TabIndex = 7;
            this.textPasswordBox.UseSystemPasswordChar = true;
            this.textPasswordBox.TextChanged += new System.EventHandler(this.textBox3_TextChanged);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.textPasswordBox);
            this.Controls.Add(this.txtUserBox);
            this.Controls.Add(this.txtServerBox);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.btnTest);
            this.Controls.Add(this.btnHello);
            this.Name = "Form1";
            this.Text = "Form1";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btnHello;
        private System.Windows.Forms.Button btnTest;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox txtServerBox;
        private System.Windows.Forms.TextBox txtUserBox;
        private System.Windows.Forms.TextBox textPasswordBox;
    }
}

