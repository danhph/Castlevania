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
    public partial class FormResize : Form
    {
        public FormResize()
        {
            InitializeComponent();
        }
        int mapWidth = 0, mapHeight = 0;
        Boolean OK = false;

        private void New_Load(object sender, EventArgs e)
        {

        }

        private void btnOK_Click(object sender, EventArgs e)
        {
            mapWidth = (int)numMapWidth.Value;
            mapHeight = (int)numMapHeight.Value;
            OK = true;
            this.Close();
        }
        public Boolean isOK
        {
            get
            {
                return OK;
            }
        }

        public int MapWidth
        {
            get
            {
                return mapWidth;
            }
        }

        private void btnCancel_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        public int MapHeight
        {
            get
            {
                return mapHeight;
            }
        }

    private void Resize_Load(object sender, EventArgs e)
        {

        }
    }
}
