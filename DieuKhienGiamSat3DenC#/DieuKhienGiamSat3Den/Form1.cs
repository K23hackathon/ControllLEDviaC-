using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace DieuKhienGiamSat3Den
{
    public partial class Form1 : Form
    {
        int[] a = new int[100];
        int[] b = new int[100];
        int m = 0, n = 0;
        int check = 0;
        int mode = 0;
        int feedback = 0;
        int current1, current2 = 0;
        public Form1()
        {
            InitializeComponent();
        }
        private void Form1_Load(object sender, EventArgs e)
        {
            Control.CheckForIllegalCrossThreadCalls = false;
            if (serialPort1.IsOpen) serialPort1.Close();
            serialPort1.Open();
            
        }
        private void LED1_Click(object sender, EventArgs e)
        {
            serialPort1.Write("@LED1ONN~");
            //serialPort1.Write("@0000111122223333*");
            feedback = 1;
            LED1.Enabled = false;
            trackBar1.Enabled = true;
            trackBar1.Value = 100;
            textBox1.Text = "100";
            OLED1.Enabled = true;
        }

        private void LED2_Click(object sender, EventArgs e)
        {
            serialPort1.Write("@LED2ONN~");
           // serialPort1.Write("@0011221133224433*");
            feedback = 2;
            LED2.Enabled = false;
            trackBar2.Enabled = true;
            trackBar2.Value = 100;
            textBox2.Text = "100";
            OLED2.Enabled = true;
        }

        private void LED3_Click(object sender, EventArgs e)
        {
            serialPort1.Write("@LED3ONN~");
            //serialPort1.Write("@0009001000110033~");
            feedback = 3;
            LED3.Enabled = false;
            trackBar3.Enabled = true;
            trackBar3.Value = 100;
            textBox3.Text = "100";
            OLED3.Enabled = true;
        }

        private void OLED1_Click(object sender, EventArgs e)
        {
            serialPort1.Write("@LED1OFF~");
            feedback = 4;
            LED1.Enabled = true;
            trackBar1.Value = 0;
            textBox1.Text = "0";
            OLED1.Enabled = false;
            VLED1.Text = "0";
         
        }

        private void OLED2_Click(object sender, EventArgs e)
        {
            serialPort1.Write("@LED2OFF~");
            feedback = 5;
            LED2.Enabled = true;
            trackBar2.Value = 0;
            textBox2.Text = "0";
            OLED2.Enabled = false;
            VLED2.Text = "0";

        }
        private void OLED3_Click(object sender, EventArgs e)
        {
            serialPort1.Write("@LED3OFF~");
            feedback = 6;
            LED3.Enabled = true;
            trackBar3.Value = 0;
            textBox3.Text = "0";
            OLED3.Enabled = false;
        }

        // Start key is: *
        // End key is : $
        int c, c1, c2, c3;
        string str;
        short flag_read = 0, flag_read0 = 0;
        private void serialPort1_DataReceived(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {
            int value1 = 0;
            int value2 = 0;
            int value3 = 0;
            int value4 = 0;
           c = serialPort1.ReadByte();
           a[n] = c;
           n++;
           if (n >= 99) n = 0;
           for (int i = 0; i < 80; i++)
           {
               if (a[i] == '@')
                   c1 = i+1;
               if (a[i] == '*')
               {
                   c2 = i;
                   goto lable;
               }
               if (a[i] == '~')
               {
                   c3 = i;
                   goto lable;
               }
           }
           lable:
           if (a[c2] == '*' && (c2 - c1) ==16)
           {
               for (int j = c1; j < c1+4; j++)
               {
                   value1 = value1 * 10 + (a[j] - 48);
               }
               for (int j = c1+4; j < c1+8; j++)
               {
                   value2 = value2 * 10 + (a[j] - 48);
               }
               for (int j = c1+8; j < c1+12; j++)
               {
                   value3 = value3 * 10 + (a[j] - 48);
               }
               for (int j = c1 + 12; j < c1 + 16; j++)
               {
                   value4 = value4 * 10 + (a[j] - 48);
               }
               if (feedback == 1)
               {
                   VLED1.Text = Convert.ToString(value1);
                   VLED2.Text = Convert.ToString(value2);
                   VLED3.Text = Convert.ToString(value3);
                   current1 = value1;
                   current2 = value2;
               }
               if (feedback == 2)
               {
                   VLED1.Text = Convert.ToString(value1);
                   VLED2.Text = Convert.ToString(value2);
                   VLED3.Text = Convert.ToString(value3);
                   current1 = value1;
                   current2 = value2;
               }
               if (feedback == 3)
               {
                   VLED1.Text = Convert.ToString(value1);
                   VLED2.Text = Convert.ToString(value2);
                   VLED3.Text = Convert.ToString(value3);
               }
               //if (feedback == 4)
               //{
               //    VLED1.Text = Convert.ToString("0");
               //    current1 = 0;
               //}
               //if (feedback == 5)
               //{
               //    VLED2.Text = Convert.ToString("0");
               //    current2 = 0;
               //}
               //if (feedback == 6)
               //{
               //    VLED3.Text = Convert.ToString("0");
               //}
               //VLED4.Text = Convert.ToString(value4);
               VLED4.Text = (current1 + current2).ToString();
               for (int o = 0; o < 100; o++)
               {
                   a[o] = 0;
               }
               n = 0;
              // serialPort1.Write("OK");
               //c1 = c2 = c3 = -1;
           }

           if (a[c3] == '~')
           {
               for (int l = c1; l < c3; l++)
               {
                   char d = Convert.ToChar(a[l]);
                   str = str + Convert.ToString(d);
                   
               }
               scan(str);
               str = " ";
               for (int o = 0; o < 100; o++)
               {
                   a[o] = 0;
               }
               n = 0;
               
               //c1 = c2 = c3 = -1;
           }
        }
        public void scan(string c)
        {
            if(c.IndexOf("LED1ON") >= 0)
            {
                CLED1.Checked = true;
                CLED1.Text = "ON";
                serialPort1.Write("OK");
            }
            if (c.IndexOf("LED2ON") >= 0)
            {
                CLED2.Checked = true;
                CLED2.Text = "ON";
                serialPort1.Write("OK");
            }
            if (c.IndexOf("LED3ON") >= 0)
            {
                CLED3.Checked = true;
                CLED3.Text = "ON";
                serialPort1.Write("OK");
            }
            if (c.IndexOf("LED1OFF") >= 0)
            {
                CLED1.Checked = false;
                CLED1.Text = "OFF";
                serialPort1.Write("OK");
            }
            if (c.IndexOf("LED2OFF") >= 0)
            {
                CLED2.Checked = false;
                CLED2.Text = "OFF";
                serialPort1.Write("OK");
            }
            if (c.IndexOf("LED3OFF") >= 0)
            {
                CLED3.Checked = false;
                CLED3.Text = "OFF";
                serialPort1.Write("OK");
            }
            
        }

        private void trackBar1_Scroll(object sender, EventArgs e)
        {
            textBox1.Text = Convert.ToString(trackBar1.Value);
            SendTrackBarValue();
        }

        private void trackBar2_Scroll(object sender, EventArgs e)
        {
            textBox2.Text = Convert.ToString(trackBar2.Value);
            SendTrackBarValue();
        }

        private void trackBar3_Scroll(object sender, EventArgs e)
        {
            textBox3.Text = Convert.ToString(trackBar3.Value);
            SendTrackBarValue();
        }

        public void SendTrackBarValue()
        {
            string trb1value = "";
            trb1value = Convert.ToString(trackBar1.Value);
            if (trackBar1.Value < 10)
                trb1value = "00" + trb1value;
            if (trackBar1.Value > 10 && trackBar1.Value < 100)
                trb1value = "0" + trb1value;

            string trb2value = "";
            trb2value = Convert.ToString(trackBar2.Value);
            if (trackBar2.Value < 10)
                trb2value = "00" + trb2value;
            if (trackBar2.Value > 10 && trackBar2.Value < 100)
                trb2value = "0" + trb2value;

            string trb3value = "";
            trb3value = Convert.ToString(trackBar3.Value);
            if (trackBar3.Value < 10)
                trb3value = "00" + trb3value;
            if (trackBar3.Value > 10 && trackBar3.Value < 100)
                trb3value = "0" + trb3value;
            string trabstring = "@" + trb1value + trb2value + trb3value + "*";
            
            serialPort1.Write(trabstring);
        }

        private void CLED3_CheckedChanged(object sender, EventArgs e)
        {

        }

        private void label2_Click(object sender, EventArgs e)
        {

        }

        private void CLED1_CheckedChanged(object sender, EventArgs e)
        {

        }

        private void label13_Click(object sender, EventArgs e)
        {

        }

        private void label10_Click(object sender, EventArgs e)
        {

        }

        private void label14_Click(object sender, EventArgs e)
        {

        }

        private void Sensor_Click(object sender, EventArgs e)
        {
            mode = 1;
            if(Sensor.Text=="Manual" && mode==1)
            {
                mode = 0;
                LED1.Enabled = true;
                LED2.Enabled = true;
                LED3.Enabled = true;
            }
            if(Sensor.Text=="Auto" && mode == 0)
            {
                mode = 1;

                LED1.Enabled = false;
                LED2.Enabled = false;
                LED3.Enabled = false;
            }
            serialPort1.Write("@sen~");
                check++;
            if(check==3)
            {
                check = 1;
            }
            if(check==1)
            {
                Sensor.Text = "Manual";
            }
            if(check==2)
            {
                Sensor.Text = "Auto";
            }
            
            
    }

        private void VLED2_TextChanged(object sender, EventArgs e)
        {

        }

        private void label6_Click(object sender, EventArgs e)
        {

        }

        private void label9_Click(object sender, EventArgs e)
        {

        }

        private void label11_Click(object sender, EventArgs e)
        {

        }

        private void pictureBox1_Click(object sender, EventArgs e)
        {

        }

        private void VLED1_TextChanged(object sender, EventArgs e)
        {

        }

        private void CLED2_CheckedChanged(object sender, EventArgs e)
        {

        }

        private void groupBox1_Enter(object sender, EventArgs e)
        {

        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            groupBox1.Text = feedback.ToString();

        }

        private void Form1_Resize(object sender, EventArgs e)
        {

        }

        private void pictureBox1_Click_1(object sender, EventArgs e)
        {

        }

        
    }
}
