using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using MapEditor.Tiles;

namespace MapEditor
{
    public partial class MainForm : Form
    {
        private TileMap tileMap;
        private TileSet tileSet;
        public MainForm()
        {
            InitializeComponent();
        }

        private void MainForm_Load(object sender, EventArgs e)
        {
            SettingForm settingForm = new SettingForm();
            if (settingForm.ShowDialog() == DialogResult.OK)
            {
                tileSet = new TileSet(settingForm.TileWidth);
                tileMap = new TileMap(settingForm.Column, settingForm.Row);
            }
            else
            {
                Application.Exit();
            }
        }
    }
}
