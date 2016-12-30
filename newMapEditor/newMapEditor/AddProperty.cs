using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace newMapEditor
{
    public partial class AddProperty : Form
    {
        public AddProperty()
        {
            InitializeComponent();
        }

        private void btnOK_Click(object sender, EventArgs e)
        {
            if (txtName.Text.Trim() != "" && txtValue.Text.Trim() != "")
            {
                property = new KeyValuePair<String, String>(txtName.Text, txtValue.Text);
            }
            else
            {
                MessageBox.Show("Ban chua nhap du thong tin property");
            }
                this.Close();
        }
        KeyValuePair<String, String> property = default(KeyValuePair<String, String>);
        public KeyValuePair<String,String> Property
        {
            get
            {
                return property;
            }
            set
            {
                property = value;
            }
        }

        private void btnCancel_Click(object sender, EventArgs e)
        {
            property = default(KeyValuePair<String, String>);
            this.Close();
        }
    }
}
