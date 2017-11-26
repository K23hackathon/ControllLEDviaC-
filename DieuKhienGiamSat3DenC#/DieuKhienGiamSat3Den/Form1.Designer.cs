namespace DieuKhienGiamSat3Den
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
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.LED1 = new System.Windows.Forms.Button();
            this.LED2 = new System.Windows.Forms.Button();
            this.LED3 = new System.Windows.Forms.Button();
            this.CLED1 = new System.Windows.Forms.CheckBox();
            this.CLED2 = new System.Windows.Forms.CheckBox();
            this.CLED3 = new System.Windows.Forms.CheckBox();
            this.VLED1 = new System.Windows.Forms.TextBox();
            this.VLED2 = new System.Windows.Forms.TextBox();
            this.VLED3 = new System.Windows.Forms.TextBox();
            this.OLED3 = new System.Windows.Forms.Button();
            this.OLED2 = new System.Windows.Forms.Button();
            this.OLED1 = new System.Windows.Forms.Button();
            this.serialPort1 = new System.IO.Ports.SerialPort(this.components);
            this.trackBar1 = new System.Windows.Forms.TrackBar();
            this.trackBar2 = new System.Windows.Forms.TrackBar();
            this.trackBar3 = new System.Windows.Forms.TrackBar();
            this.VLED4 = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.textBox2 = new System.Windows.Forms.TextBox();
            this.textBox3 = new System.Windows.Forms.TextBox();
            this.Sensor = new System.Windows.Forms.Button();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.label4 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            ((System.ComponentModel.ISupportInitialize)(this.trackBar1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBar2)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBar3)).BeginInit();
            this.groupBox1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.SuspendLayout();
            // 
            // LED1
            // 
            this.LED1.Location = new System.Drawing.Point(105, 165);
            this.LED1.Margin = new System.Windows.Forms.Padding(6);
            this.LED1.Name = "LED1";
            this.LED1.Size = new System.Drawing.Size(138, 42);
            this.LED1.TabIndex = 0;
            this.LED1.Text = "LED1";
            this.LED1.UseVisualStyleBackColor = true;
            this.LED1.Click += new System.EventHandler(this.LED1_Click);
            // 
            // LED2
            // 
            this.LED2.Location = new System.Drawing.Point(273, 165);
            this.LED2.Margin = new System.Windows.Forms.Padding(6);
            this.LED2.Name = "LED2";
            this.LED2.Size = new System.Drawing.Size(138, 42);
            this.LED2.TabIndex = 1;
            this.LED2.Text = "LED2";
            this.LED2.UseVisualStyleBackColor = true;
            this.LED2.Click += new System.EventHandler(this.LED2_Click);
            // 
            // LED3
            // 
            this.LED3.Location = new System.Drawing.Point(861, 248);
            this.LED3.Margin = new System.Windows.Forms.Padding(6);
            this.LED3.Name = "LED3";
            this.LED3.Size = new System.Drawing.Size(138, 42);
            this.LED3.TabIndex = 2;
            this.LED3.Text = "LED3";
            this.LED3.UseVisualStyleBackColor = true;
            this.LED3.Click += new System.EventHandler(this.LED3_Click);
            // 
            // CLED1
            // 
            this.CLED1.AutoSize = true;
            this.CLED1.Enabled = false;
            this.CLED1.ForeColor = System.Drawing.Color.Red;
            this.CLED1.Location = new System.Drawing.Point(123, 297);
            this.CLED1.Margin = new System.Windows.Forms.Padding(6);
            this.CLED1.Name = "CLED1";
            this.CLED1.Size = new System.Drawing.Size(78, 29);
            this.CLED1.TabIndex = 3;
            this.CLED1.Text = "OFF";
            this.CLED1.UseVisualStyleBackColor = true;
            this.CLED1.CheckedChanged += new System.EventHandler(this.CLED1_CheckedChanged);
            // 
            // CLED2
            // 
            this.CLED2.AutoSize = true;
            this.CLED2.Enabled = false;
            this.CLED2.ForeColor = System.Drawing.Color.Red;
            this.CLED2.Location = new System.Drawing.Point(303, 297);
            this.CLED2.Margin = new System.Windows.Forms.Padding(6);
            this.CLED2.Name = "CLED2";
            this.CLED2.Size = new System.Drawing.Size(78, 29);
            this.CLED2.TabIndex = 4;
            this.CLED2.Text = "OFF";
            this.CLED2.UseVisualStyleBackColor = true;
            this.CLED2.CheckedChanged += new System.EventHandler(this.CLED2_CheckedChanged);
            // 
            // CLED3
            // 
            this.CLED3.AutoSize = true;
            this.CLED3.Enabled = false;
            this.CLED3.ForeColor = System.Drawing.Color.Red;
            this.CLED3.Location = new System.Drawing.Point(893, 381);
            this.CLED3.Margin = new System.Windows.Forms.Padding(6);
            this.CLED3.Name = "CLED3";
            this.CLED3.Size = new System.Drawing.Size(78, 29);
            this.CLED3.TabIndex = 5;
            this.CLED3.Text = "OFF";
            this.CLED3.UseVisualStyleBackColor = true;
            this.CLED3.CheckedChanged += new System.EventHandler(this.CLED3_CheckedChanged);
            // 
            // VLED1
            // 
            this.VLED1.Location = new System.Drawing.Point(105, 340);
            this.VLED1.Margin = new System.Windows.Forms.Padding(6);
            this.VLED1.Name = "VLED1";
            this.VLED1.ReadOnly = true;
            this.VLED1.Size = new System.Drawing.Size(134, 29);
            this.VLED1.TabIndex = 6;
            this.VLED1.TextChanged += new System.EventHandler(this.VLED1_TextChanged);
            // 
            // VLED2
            // 
            this.VLED2.Location = new System.Drawing.Point(271, 340);
            this.VLED2.Margin = new System.Windows.Forms.Padding(6);
            this.VLED2.Name = "VLED2";
            this.VLED2.ReadOnly = true;
            this.VLED2.Size = new System.Drawing.Size(134, 29);
            this.VLED2.TabIndex = 7;
            this.VLED2.TextChanged += new System.EventHandler(this.VLED2_TextChanged);
            // 
            // VLED3
            // 
            this.VLED3.Location = new System.Drawing.Point(861, 423);
            this.VLED3.Margin = new System.Windows.Forms.Padding(6);
            this.VLED3.Name = "VLED3";
            this.VLED3.ReadOnly = true;
            this.VLED3.Size = new System.Drawing.Size(134, 29);
            this.VLED3.TabIndex = 8;
            // 
            // OLED3
            // 
            this.OLED3.Enabled = false;
            this.OLED3.Location = new System.Drawing.Point(861, 327);
            this.OLED3.Margin = new System.Windows.Forms.Padding(6);
            this.OLED3.Name = "OLED3";
            this.OLED3.Size = new System.Drawing.Size(138, 42);
            this.OLED3.TabIndex = 11;
            this.OLED3.Text = "OFF3";
            this.OLED3.UseVisualStyleBackColor = true;
            this.OLED3.Click += new System.EventHandler(this.OLED3_Click);
            // 
            // OLED2
            // 
            this.OLED2.Enabled = false;
            this.OLED2.Location = new System.Drawing.Point(271, 244);
            this.OLED2.Margin = new System.Windows.Forms.Padding(6);
            this.OLED2.Name = "OLED2";
            this.OLED2.Size = new System.Drawing.Size(138, 42);
            this.OLED2.TabIndex = 10;
            this.OLED2.Text = "OFF2";
            this.OLED2.UseVisualStyleBackColor = true;
            this.OLED2.Click += new System.EventHandler(this.OLED2_Click);
            // 
            // OLED1
            // 
            this.OLED1.Enabled = false;
            this.OLED1.Location = new System.Drawing.Point(105, 244);
            this.OLED1.Margin = new System.Windows.Forms.Padding(6);
            this.OLED1.Name = "OLED1";
            this.OLED1.Size = new System.Drawing.Size(138, 42);
            this.OLED1.TabIndex = 9;
            this.OLED1.Text = "OFF1";
            this.OLED1.UseVisualStyleBackColor = true;
            this.OLED1.Click += new System.EventHandler(this.OLED1_Click);
            // 
            // serialPort1
            // 
            this.serialPort1.PortName = "COM3";
            this.serialPort1.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.serialPort1_DataReceived);
            // 
            // trackBar1
            // 
            this.trackBar1.AllowDrop = true;
            this.trackBar1.Location = new System.Drawing.Point(70, 50);
            this.trackBar1.Margin = new System.Windows.Forms.Padding(6);
            this.trackBar1.Maximum = 100;
            this.trackBar1.Name = "trackBar1";
            this.trackBar1.Size = new System.Drawing.Size(191, 80);
            this.trackBar1.TabIndex = 13;
            this.trackBar1.Scroll += new System.EventHandler(this.trackBar1_Scroll);
            // 
            // trackBar2
            // 
            this.trackBar2.Location = new System.Drawing.Point(249, 50);
            this.trackBar2.Margin = new System.Windows.Forms.Padding(6);
            this.trackBar2.Maximum = 100;
            this.trackBar2.Name = "trackBar2";
            this.trackBar2.Size = new System.Drawing.Size(191, 80);
            this.trackBar2.TabIndex = 14;
            this.trackBar2.Scroll += new System.EventHandler(this.trackBar2_Scroll);
            // 
            // trackBar3
            // 
            this.trackBar3.Enabled = false;
            this.trackBar3.Location = new System.Drawing.Point(826, 133);
            this.trackBar3.Margin = new System.Windows.Forms.Padding(6);
            this.trackBar3.Maximum = 100;
            this.trackBar3.Name = "trackBar3";
            this.trackBar3.Size = new System.Drawing.Size(191, 80);
            this.trackBar3.TabIndex = 15;
            this.trackBar3.Scroll += new System.EventHandler(this.trackBar3_Scroll);
            // 
            // VLED4
            // 
            this.VLED4.Location = new System.Drawing.Point(310, 440);
            this.VLED4.Margin = new System.Windows.Forms.Padding(6);
            this.VLED4.Name = "VLED4";
            this.VLED4.ReadOnly = true;
            this.VLED4.Size = new System.Drawing.Size(134, 29);
            this.VLED4.TabIndex = 16;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(236, 445);
            this.label2.Margin = new System.Windows.Forms.Padding(6, 0, 6, 0);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(62, 25);
            this.label2.TabIndex = 17;
            this.label2.Text = "ISUM";
            this.label2.Click += new System.EventHandler(this.label2_Click);
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(919, 465);
            this.label6.Margin = new System.Windows.Forms.Padding(6, 0, 6, 0);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(42, 25);
            this.label6.TabIndex = 21;
            this.label6.Text = "mA";
            this.label6.Click += new System.EventHandler(this.label6_Click);
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(158, 382);
            this.label7.Margin = new System.Windows.Forms.Padding(6, 0, 6, 0);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(42, 25);
            this.label7.TabIndex = 22;
            this.label7.Text = "mA";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(315, 382);
            this.label8.Margin = new System.Windows.Forms.Padding(6, 0, 6, 0);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(42, 25);
            this.label8.TabIndex = 23;
            this.label8.Text = "mA";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(458, 453);
            this.label9.Margin = new System.Windows.Forms.Padding(6, 0, 6, 0);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(42, 25);
            this.label9.TabIndex = 24;
            this.label9.Text = "mA";
            this.label9.Click += new System.EventHandler(this.label9_Click);
            // 
            // textBox1
            // 
            this.textBox1.Location = new System.Drawing.Point(141, 117);
            this.textBox1.Margin = new System.Windows.Forms.Padding(6);
            this.textBox1.Name = "textBox1";
            this.textBox1.ReadOnly = true;
            this.textBox1.Size = new System.Drawing.Size(63, 29);
            this.textBox1.TabIndex = 27;
            // 
            // textBox2
            // 
            this.textBox2.Location = new System.Drawing.Point(321, 117);
            this.textBox2.Margin = new System.Windows.Forms.Padding(6);
            this.textBox2.Name = "textBox2";
            this.textBox2.ReadOnly = true;
            this.textBox2.Size = new System.Drawing.Size(63, 29);
            this.textBox2.TabIndex = 28;
            // 
            // textBox3
            // 
            this.textBox3.Location = new System.Drawing.Point(893, 204);
            this.textBox3.Margin = new System.Windows.Forms.Padding(6);
            this.textBox3.Name = "textBox3";
            this.textBox3.ReadOnly = true;
            this.textBox3.Size = new System.Drawing.Size(63, 29);
            this.textBox3.TabIndex = 29;
            // 
            // Sensor
            // 
            this.Sensor.ForeColor = System.Drawing.Color.Coral;
            this.Sensor.Location = new System.Drawing.Point(48, 440);
            this.Sensor.Margin = new System.Windows.Forms.Padding(6);
            this.Sensor.Name = "Sensor";
            this.Sensor.Size = new System.Drawing.Size(138, 42);
            this.Sensor.TabIndex = 35;
            this.Sensor.Text = "Start";
            this.Sensor.UseVisualStyleBackColor = true;
            this.Sensor.Click += new System.EventHandler(this.Sensor_Click);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.label4);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Controls.Add(this.LED1);
            this.groupBox1.Controls.Add(this.Sensor);
            this.groupBox1.Controls.Add(this.LED2);
            this.groupBox1.Controls.Add(this.textBox2);
            this.groupBox1.Controls.Add(this.CLED1);
            this.groupBox1.Controls.Add(this.textBox1);
            this.groupBox1.Controls.Add(this.CLED2);
            this.groupBox1.Controls.Add(this.label9);
            this.groupBox1.Controls.Add(this.label8);
            this.groupBox1.Controls.Add(this.VLED1);
            this.groupBox1.Controls.Add(this.label7);
            this.groupBox1.Controls.Add(this.VLED2);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.OLED1);
            this.groupBox1.Controls.Add(this.VLED4);
            this.groupBox1.Controls.Add(this.OLED2);
            this.groupBox1.Controls.Add(this.trackBar2);
            this.groupBox1.Controls.Add(this.trackBar1);
            this.groupBox1.Location = new System.Drawing.Point(536, 44);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(502, 509);
            this.groupBox1.TabIndex = 37;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "CONTROL PANEL";
            this.groupBox1.Enter += new System.EventHandler(this.groupBox1_Enter);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(393, 121);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(30, 25);
            this.label4.TabIndex = 36;
            this.label4.Text = "%";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(209, 117);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(30, 25);
            this.label1.TabIndex = 36;
            this.label1.Text = "%";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 15F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label3.ForeColor = System.Drawing.Color.Brown;
            this.label3.Location = new System.Drawing.Point(48, 32);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(456, 39);
            this.label3.TabIndex = 38;
            this.label3.Text = "Binh Duong Hackathon 2017";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(965, 204);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(30, 25);
            this.label5.TabIndex = 36;
            this.label5.Text = "%";
            // 
            // timer1
            // 
            this.timer1.Enabled = true;
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // pictureBox1
            // 
            this.pictureBox1.Image = ((System.Drawing.Image)(resources.GetObject("pictureBox1.Image")));
            this.pictureBox1.Location = new System.Drawing.Point(30, 92);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(500, 438);
            this.pictureBox1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.pictureBox1.TabIndex = 39;
            this.pictureBox1.TabStop = false;
            this.pictureBox1.Click += new System.EventHandler(this.pictureBox1_Click_1);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(11F, 24F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1061, 565);
            this.Controls.Add(this.pictureBox1);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.trackBar3);
            this.Controls.Add(this.OLED3);
            this.Controls.Add(this.VLED3);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.textBox3);
            this.Controls.Add(this.CLED3);
            this.Controls.Add(this.LED3);
            this.Margin = new System.Windows.Forms.Padding(6);
            this.Name = "Form1";
            this.Text = "0O";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.Resize += new System.EventHandler(this.Form1_Resize);
            ((System.ComponentModel.ISupportInitialize)(this.trackBar1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBar2)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.trackBar3)).EndInit();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button LED1;
        private System.Windows.Forms.Button LED2;
        private System.Windows.Forms.Button LED3;
        private System.Windows.Forms.CheckBox CLED1;
        private System.Windows.Forms.CheckBox CLED2;
        private System.Windows.Forms.CheckBox CLED3;
        private System.Windows.Forms.TextBox VLED1;
        private System.Windows.Forms.TextBox VLED2;
        private System.Windows.Forms.TextBox VLED3;
        private System.Windows.Forms.Button OLED3;
        private System.Windows.Forms.Button OLED2;
        private System.Windows.Forms.Button OLED1;
        private System.IO.Ports.SerialPort serialPort1;
        private System.Windows.Forms.TrackBar trackBar1;
        private System.Windows.Forms.TrackBar trackBar2;
        private System.Windows.Forms.TrackBar trackBar3;
        private System.Windows.Forms.TextBox VLED4;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.TextBox textBox2;
        private System.Windows.Forms.TextBox textBox3;
        private System.Windows.Forms.Button Sensor;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.PictureBox pictureBox1;
    }
}

