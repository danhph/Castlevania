using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace MapEditor
{
    public partial class SettingForm : Form
    {
        public int Column { get; set; }
        public int Row { get; set; }
        public int TileWidth { get; set; }

        public SettingForm()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                this.Column = Convert.ToInt32(this.column.Text);
                this.Row = Convert.ToInt32(this.row.Text);
                this.TileWidth = Convert.ToInt32(this.width.Text);
                this.DialogResult = DialogResult.OK;
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.ToString());
            }
        }
    }
}
