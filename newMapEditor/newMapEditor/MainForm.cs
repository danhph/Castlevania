using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Xml;

public enum State
{
    isDrawing = 0x01,
    DrawObject = 0x02,
    DrawBackGround = 0x04,
}
namespace newMapEditor
{
    public partial class MainForm : Form
    {
        //float scaleFactor;
        float scaleFactor = 1;
        State state;
        List<Objects> listObject = new List<Objects>();
        int mapWidth = 0, mapHeight = 0;
        Background background;
        PictureBox curItemBackground = null;
        TileSet tileset;
        public MainForm()
        {
            InitializeComponent();
        }





        private void menuStrip1_ItemClicked(object sender, ToolStripItemClickedEventArgs e)
        {

        }

        private void MainForm_Load(object sender, EventArgs e)
        {


        }
        private void UpdatePanelTileSet()
        {
            panel2.Controls.Clear();
            for (int i = 0; i < tileset.Count; i++)
            {
                PictureBox pictureBox = new System.Windows.Forms.PictureBox();
                pictureBox.Location = new System.Drawing.Point((i % tileset.Columns) * 32 + (i % tileset.Columns), (i / tileset.Columns) * 32 + (i / tileset.Columns));
                pictureBox.Name = "pic" + i.ToString();
                pictureBox.BackgroundImageLayout = ImageLayout.Stretch;
                pictureBox.Size = new System.Drawing.Size(32, 32);
                pictureBox.Tag = i.ToString();
                pictureBox.BackgroundImage = tileset[i + 1].Image;
                pictureBox.MouseClick += new System.Windows.Forms.MouseEventHandler(picItem_MouseClick);
                panel2.Controls.Add(pictureBox);
            }
        }
        private void btnAdd_Click(object sender, EventArgs e)
        {

            CreateTileSet frmCreateTS = new CreateTileSet();
            do
            {
                frmCreateTS.ShowDialog();
                if (frmCreateTS.isOK && frmCreateTS.TileSet != null)
                {
                    tileset = frmCreateTS.TileSet;
                    InitBackground();
                    UpdatePanelTileSet();
                }
                else
                    tileset = null;
            }
            while (tileset == null && frmCreateTS.isCancel == false);

        }
        private void updateSizePicmain(float scaleFactor = 1)
        {
            picMain.Width = (int)(background.MapWidth * tileset.TileWidth * scaleFactor) + 1;
            picMain.Height = (int)(background.MapHeight * tileset.TileHeight * scaleFactor) + 1;
        }
        private void InitBackground()
        {
            if (tileset != null && mapWidth > 0 && mapHeight > 0)
            {
                background = new Background(tileset, mapWidth, mapHeight);
                //buffer = new Bitmap(mapWidth * tileset.TileWidth, mapHeight * tileset.TileHeight);
                //gBuffer = Graphics.FromImage(buffer);
                Draw();
            }
            else
                return;
        }

        private void newToolStripMenuItem_Click(object sender, EventArgs e)
        {
            New frmNew = new New();
            frmNew.ShowDialog();
            if (frmNew.isOK)
            {
                mapWidth = frmNew.MapWidth;
                mapHeight = frmNew.MapHeight;
                InitBackground();
            }
        }

        private void picMain_MouseClick(object sender, MouseEventArgs e)
        {
            try
            {
                if ((state & State.DrawBackGround) == State.DrawBackGround)
                {
                    int X = e.X / (int)(tileset.TileWidth * scaleFactor);
                    int Y = e.Y / (int)(tileset.TileHeight * scaleFactor);
                    if (e.Button == MouseButtons.Right)
                    {
                        background[Y, X] = -1;
                    }

                    else if (curItemBackground != null)
                    {
                        background[Y, X] = int.Parse(curItemBackground.Tag.ToString());
                    }
                }
                Draw();
            }
            catch
            {
            }
        }
        int startX = 0, startY = 0;
        int endX = 0, endY = 0;

        private void picMain_MouseMove(object sender, MouseEventArgs e)
        {
            try
            {
                endX = e.X;
                endY = e.Y;
                if ((state & State.isDrawing) == State.isDrawing && (state & State.DrawObject) == State.DrawObject && e.Button == MouseButtons.Left)
                {
                    Draw();//Draw();
                    Graphics g = Graphics.FromImage(picMain.Image);
                    g.FillRectangle(new SolidBrush(Color.FromArgb(64, 0, 0, 255)), new Rectangle(startX, startY, endX - startX, endY - startY));

                }
                if ((state & State.isDrawing) == State.isDrawing && (state & State.DrawBackGround) == State.DrawBackGround)
                {
                    int X = e.X / (int)(tileset.TileWidth * scaleFactor);
                    int Y = e.Y / (int)(tileset.TileHeight * scaleFactor);
                    if (e.Button == MouseButtons.Right)
                    {
                        background[Y, X] = -1;
                        Draw();
                    }
                    else if (curItemBackground != null)
                    {
                        background[Y, X] = int.Parse(curItemBackground.Tag.ToString());
                        Draw();
                    }
                }
            }
            catch
            {

            }
        }

        private void btnDrawObject_Click(object sender, EventArgs e)
        {
            state = (state | State.DrawObject) & (~State.DrawBackGround);
        }

        private void panel2_Click(object sender, EventArgs e)
        {
            state = (state | State.DrawBackGround) & (~State.DrawObject);
        }

        private void picMain_MouseDown(object sender, MouseEventArgs e)
        {
            state = state | State.isDrawing;
            startX = e.X;
            startY = e.Y;

        }
        Objects selectedObject;
        private void lstObject_ItemSelectionChanged(object sender, ListViewItemSelectionChangedEventArgs e)
        {
            foreach (Objects obj in listObject)
            {
                if (obj["id"] == e.Item.Tag.ToString())
                {
                    proObject.SelectedObject = new DictionaryPropertyGridAdapter(obj.Property);
                    selectedObject = obj;
                    break;
                }
            }
            foreach (Objects obj in listObject)
            {
                obj.Selected = false;
            }
            foreach (Objects obj in listObject)
            {
                if (obj["id"] == e.Item.Tag.ToString())
                {
                    obj.Selected = true;
                    break;
                }
            }
            selectedAttribute = null;
            Draw();
        }

        private void proObject_PropertyValueChanged(object s, PropertyValueChangedEventArgs e)
        {
            UpdateListObject();
            Draw();
        }

        private void lstObject_KeyPress(object sender, KeyPressEventArgs e)
        {
            //if (e.KeyChar == Keys.Delete)
        }

        private void lstObject_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyData == Keys.Delete)
            {
                foreach (Objects obj in listObject)
                {
                    if (obj["id"] == lstObject.FocusedItem.Tag.ToString())
                    {
                        listObject.Remove(obj);
                        lstObject.Items.Remove(lstObject.FocusedItem);
                        proObject.SelectedObject = null;
                        break;
                    }
                }
                Draw();
            }
        }

        private void saveToolStripMenuItem_Click(object sender, EventArgs e)
        {
            SaveFileDialog saveFileDialog1 = new SaveFileDialog();

            saveFileDialog1.Filter = "tile files (*.tile)|*.tile|All files (*.*)|*.*";
            saveFileDialog1.FilterIndex = 2;
            saveFileDialog1.RestoreDirectory = true;

            if (saveFileDialog1.ShowDialog() == DialogResult.OK)
            {

                //if (saveFileDialog1.FileName == null|| saveFileDialog1.FileName.Trim()=="") return;
                XmlWriterSettings xmlWriterSettings = new XmlWriterSettings()
                {
                    Indent = true,
                    IndentChars = "\t",
                    NewLineOnAttributes = true
                };
                using (XmlWriter writer = XmlWriter.Create(saveFileDialog1.FileName, xmlWriterSettings))
                {




                    writer.WriteStartDocument();
                    //writer.WriteString("\n");
                    writer.WriteStartElement("map");
                    writer.WriteAttributeString("width", background.MapWidth.ToString());
                    writer.WriteAttributeString("height", background.MapHeight.ToString());
                    writer.WriteAttributeString("tilewidth", background.TileSet.TileWidth.ToString());
                    writer.WriteAttributeString("tileheight", background.TileSet.TileHeight.ToString());
                    //writer.WriteEnd();
                    writer.WriteStartElement("tileset");
                    writer.WriteAttributeString("name", background.TileSet.Name);
                    writer.WriteAttributeString("firstgid", "1");
                    writer.WriteAttributeString("height", background.MapHeight.ToString());
                    writer.WriteAttributeString("tilewidth", background.TileSet.TileWidth.ToString());
                    writer.WriteAttributeString("tileheight", background.TileSet.TileHeight.ToString());
                    writer.WriteAttributeString("tilecount", background.TileSet.Count.ToString());
                    writer.WriteAttributeString("columns", background.TileSet.Columns.ToString());
                    writer.WriteAttributeString("rows", background.TileSet.Rows.ToString());
                    writer.WriteStartElement("image");
                    writer.WriteAttributeString("source", background.TileSet.Name);
                    writer.WriteAttributeString("width", background.TileSet.Image.Width.ToString());
                    writer.WriteAttributeString("rows", background.TileSet.Image.Height.ToString());
                    writer.WriteEndElement();
                    writer.WriteEndElement();
                    writer.WriteStartElement("layer");
                    writer.WriteAttributeString("width", background.MapWidth.ToString());
                    writer.WriteAttributeString("height", background.MapHeight.ToString());
                    writer.WriteStartElement("data");
                    for (int i = 0; i < background.MapHeight; i++)
                        for (int j = 0; j < background.MapWidth; j++)
                        {
                            writer.WriteStartElement("tile");
                            writer.WriteAttributeString("gid", background[i, j].ToString());
                            writer.WriteEndElement();
                        }
                    writer.WriteEndElement();
                    writer.WriteEndElement();
                    writer.WriteStartElement("objectgroup");
                    foreach (Objects obj in listObject)
                    {
                        writer.WriteStartElement("object");
                        foreach (var attribute in obj.Property)
                            if ( Array.IndexOf(new String[] { "id", "name", "x", "y", "width", "height", "type" },attribute.Key)>-1 )
                                writer.WriteAttributeString(attribute.Key, attribute.Value);
                        if (obj.Property.Count>7)
                        {
                            writer.WriteStartElement("properties");
                            foreach (var attribute in obj.Property)
                                if (Array.IndexOf(new String[] { "id", "name", "x", "y", "width", "height", "type" }, attribute.Key) < 0)
                                {
                                    writer.WriteStartElement("property");
                                    writer.WriteAttributeString("name", attribute.Key);
                                    writer.WriteAttributeString("value", attribute.Value);
                                    writer.WriteEndElement();
                                }
                            writer.WriteEndElement();
                        }
                        writer.WriteEndElement();
                    }
                    writer.WriteEndElement();
                    writer.WriteEndElement();
                    writer.WriteEndDocument();
                }

            }
        }

        private void btnDelete_Click(object sender, EventArgs e)
        {
            tileset = null;
            background.resetBackground();
            background.TileSet = null;
            panel2.Controls.Clear();
            Draw();
        }

        private void resizeToolStripMenuItem_Click(object sender, EventArgs e)
        {
            FormResize frmResize = new FormResize();
            frmResize.ShowDialog();
            if (frmResize.isOK)
            {
                int[][] newbackground = new int[frmResize.MapHeight][];
                for (int i = 0; i < frmResize.MapHeight; i++)
                {
                    newbackground[i] = new int[frmResize.MapWidth];
                }
                for (int i = 0; i < frmResize.MapHeight; i++)
                    for (int j = 0; j < frmResize.MapWidth; j++)
                    {
                        newbackground[i][j] = -1;
                    }
                if (background.MapHeight > frmResize.MapHeight || background.MapWidth > frmResize.MapWidth)
                {
                    if (MessageBox.Show("Kich co moi nho hon kich co cu, co the mat du lieu, ban co tiep tuc?", "Xac nhan", MessageBoxButtons.OKCancel, MessageBoxIcon.Warning) == DialogResult.Cancel)
                        return;
                }
                for (int i = 0; i < Math.Min(background.MapHeight, frmResize.MapHeight); i++)
                    for (int j = 0; j < Math.Min(background.MapWidth, frmResize.MapWidth); j++)
                    {
                        newbackground[i][j] = background[i, j];
                    }
                background = new Background(background.TileSet, frmResize.MapWidth, frmResize.MapHeight, newbackground);
                Draw();

            }
        }

        private void panel2_MouseEnter(object sender, EventArgs e)
        {
            panel2.Focus();
        }

        private void panel1_MouseEnter(object sender, EventArgs e)
        {
            panel1.Focus();
        }

        private void openToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OpenFileDialog openFileDialog1 = new OpenFileDialog();
            openFileDialog1.Filter = "tmx files (*.tmx)|*.tmx|All files (*.*)|*.*";
            openFileDialog1.FilterIndex = 2;
            openFileDialog1.RestoreDirectory = true;

            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {

                XmlDocument doc = new XmlDocument();
                doc.Load(openFileDialog1.FileName);
                XmlNode xmlMap = doc.SelectSingleNode("/map");
                XmlNode xmlTileset = doc.SelectSingleNode("/map/tileset");
                XmlNode xmlTilesetImage = doc.SelectSingleNode("/map/tileset/image");
                string name = xmlTilesetImage.Attributes["source"].Value.ToString();
                string[] arrSource = openFileDialog1.FileName.Split(new String[] { "\\" }, StringSplitOptions.RemoveEmptyEntries);
                arrSource[arrSource.Length - 1] = name;
                string source = "";
                for (int i = 0; i < arrSource.Length; i++)
                {
                    source += arrSource[i] + (i == (arrSource.Length - 1) ? "" : "\\");
                }
                tileset = new TileSet(name, source, int.Parse(xmlTileset.Attributes["tilewidth"].Value.ToString()), int.Parse(xmlTileset.Attributes["tileheight"].Value.ToString()));
                int width = int.Parse(xmlMap.Attributes["width"].Value.ToString());
                int height = int.Parse(xmlMap.Attributes["height"].Value.ToString());
                background = new Background(tileset, width, height);
                XmlNodeList arrBackground = doc.SelectNodes("/map/layer/data/tile");
                for (int i = 0; i < background.MapHeight; i++)
                    for (int j = 0; j < background.MapWidth; j++)
                    {
                        XmlNode tileId = arrBackground.Item(i * background.MapWidth + j).Attributes["gid"];
                        background[i, j] = int.Parse(tileId.Value.ToString());
                    }
                UpdatePanelTileSet();
                //try
                //{
                XmlNodeList objects = doc.SelectNodes("/map/objectgroup/object");
                if (objects.Count > 0)
                {
                    listObject.Clear();
                    lstObject.Items.Clear();
                    proObject.SelectedObject = null;
                    foreach (XmlNode obj in objects)
                    {
                        Objects newObject = new Objects(int.Parse(obj.Attributes["id"].Value), obj.Attributes["name"].Value, int.Parse(obj.Attributes["type"].Value), float.Parse(obj.Attributes["x"].Value), float.Parse(obj.Attributes["y"].Value), float.Parse(obj.Attributes["width"].Value), float.Parse(obj.Attributes["height"].Value));
                        if (obj.HasChildNodes)
                        {
                            XmlNodeList properties = obj.ChildNodes[0].ChildNodes;
                            if (properties.Count > 0)
                            {
                                foreach (XmlNode attribute in properties)
                                {
                                    newObject.Property.Add(attribute.Attributes["name"].Value, attribute.Attributes["value"].Value);
                                }
                            }
                        }
                        listObject.Add(newObject);
                        UpdateListObject(newObject);
                    }
                    Objects.count = int.Parse(objects.Item(objects.Count - 1).Attributes["id"].Value) + 1;
                }
                //}
                //catch (NullReferenceException)
                //{
                //    MessageBox.Show("Map nay chua co object");
                //}
                Draw();

            }

        }
        private void updateScaleFactor(Panel panel, Background bg)
        {
            scaleFactor = Math.Max((float)panel.Width / (bg.MapWidth * bg.TileSet.TileWidth), (float)panel.Height / (bg.MapHeight * bg.TileSet.TileHeight));
        }
        private void Draw()
        {
            //try
            //{

            updateScaleFactor(panel1, background);
            //updateSizePicmain();
            Bitmap buffer = new Bitmap((int)(background.MapWidth * background.TileSet.TileWidth * scaleFactor) + 1, (int)(background.MapHeight * background.TileSet.TileHeight * scaleFactor) + 1);
            Graphics gBuffer = Graphics.FromImage(buffer);
            background.Draw(gBuffer, scaleFactor);
            foreach (Objects obj in listObject)
            {
                obj.Draw(gBuffer, scaleFactor);
            }
            for (int i = 0; i <= background.MapWidth; i++)
            {
                gBuffer.DrawLine(new Pen(Color.Blue, 1), new Point((int)(i * background.TileSet.TileWidth * scaleFactor), 0), new Point((int)(i * background.TileSet.TileWidth * scaleFactor), (int)(background.MapHeight * background.TileSet.TileHeight * scaleFactor)));
            }
            for (int i = 0; i <= background.MapHeight; i++)
            {
                gBuffer.DrawLine(new Pen(Color.Blue, 1), new Point(0, (int)(i * background.TileSet.TileHeight * scaleFactor)), new Point((int)(background.MapWidth * background.TileSet.TileWidth * scaleFactor), (int)(i * background.TileSet.TileHeight * scaleFactor)));
            }
            updateSizePicmain(scaleFactor);
            //Bitmap scaleBuffer = new Bitmap(buffer, picMain.Size);
            //gPicMain.DrawImage(buffer, new Rectangle(0, 0, panel1.Width, panel1.Height), new Rectangle(0, 0, image.Width, image.Height), GraphicsUnit.Pixel);

            picMain.Image = buffer;

            //picMain.Image = buffer;
            //}
            //catch
            //{
            //  picMain.Image = null;
            //}
        }

        private void button1_Click(object sender, EventArgs e)
        {
            lstObject.Items.Clear();
            listObject.Clear();
            proObject.SelectedObject = null;
            Draw();
        }

        private void panel1_SizeChanged(object sender, EventArgs e)
        {
            try
            {
                updateScaleFactor(panel1, background);
                Draw();
            }
            catch { }
        }

        private void btnAddProperty_Click(object sender, EventArgs e)
        {
            AddProperty frmAddPro = new AddProperty();
            frmAddPro.ShowDialog();
            KeyValuePair<String, String> myproperty = frmAddPro.Property;
            selectedObject[myproperty.Key] = myproperty.Value;
            proObject.SelectedObject = new DictionaryPropertyGridAdapter(selectedObject.Property);
        }
        private void UpdateListObject()
        {
            lstObject.Items.Clear();
            foreach (var obj in listObject)
            {
                UpdateListObject(obj);
            }
        }
        string selectedAttribute;
        private void proObject_SelectedGridItemChanged(object sender, SelectedGridItemChangedEventArgs e)
        {
            selectedAttribute = e.NewSelection.PropertyDescriptor.Name;
        }

        private void btnRemoveProperty_Click(object sender, EventArgs e)
        {
            if (selectedAttribute == "x" || selectedAttribute == "y" || selectedAttribute == "id" || selectedAttribute == "name"
                || selectedAttribute == "width" || selectedAttribute == "height" || selectedAttribute == null || selectedAttribute == "type"
            )
            {
                MessageBox.Show("Khong the xoa");
            }
            else
            {
                selectedObject.Property.Remove(selectedAttribute);
                selectedAttribute = null;
                proObject.SelectedObject = new DictionaryPropertyGridAdapter(selectedObject.Property);
            }
        }

        private void UpdateListObject(Objects newObject)
        {
            ListViewItem listViewItem = new ListViewItem(new String[] { newObject["name"], newObject["type"] });
            listViewItem.Tag = newObject["id"];
            lstObject.Items.AddRange(new System.Windows.Forms.ListViewItem[] {
                listViewItem});
        }
        private void picMain_MouseUp(object sender, MouseEventArgs e)
        {
            if (((state & State.isDrawing) == State.isDrawing) && (state & State.DrawObject) == State.DrawObject && e.Button == MouseButtons.Left)
            {
                Objects newObject = new Objects((int)(startX / scaleFactor), (int)(startY / scaleFactor), (int)((endX - startX) / scaleFactor), (int)((endY - startY) / scaleFactor));
                proObject.SelectedObject = new DictionaryPropertyGridAdapter(newObject.Property);
                UpdateListObject(newObject);
                listObject.Add(newObject);
                Draw();
            }
            state = state & (~State.isDrawing);
        }

        private void picItem_MouseClick(object sender, MouseEventArgs e)
        {

            curItemBackground = (PictureBox)sender;
            state = (state | State.DrawBackGround) & (~State.DrawObject);
        }

    }
}
