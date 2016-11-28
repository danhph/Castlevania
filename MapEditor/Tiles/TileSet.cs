using System.Collections.Generic;
using System.Drawing;
using System.IO;
using System.Xml;

namespace MapEditor.Tiles
{
    public class TileSet
    {
        public TileSet(int width)
        {
            this.Width = width;
            ListTiles = new List<Tile>();
        }

        public string FileName { get; set; }

        public int Width { get; set; }

        public int Column { get; set; }

        public int Row { get; set; }

        public Image Image { get; set; }

        public List<Tile> ListTiles { get; set; }

        public static void Save(XmlTextWriter writer, TileSet tileSet, string fileName)
        {
            writer.WriteStartElement("TileSet");
            {
                writer.WriteAttributeString("Column", tileSet.Column.ToString());
                writer.WriteAttributeString("Row", tileSet.Row.ToString());
                writer.WriteAttributeString("Width", tileSet.Width.ToString());

                var imagefilename = tileSet.FileName.Substring(tileSet.FileName.LastIndexOf(@"\") + 1);
                writer.WriteAttributeString("FileName", imagefilename);

                var imagefullpath = fileName.Substring(0, fileName.LastIndexOf('\\')) + @"\\" + imagefilename;
                if (File.Exists(imagefullpath) == false)
                    File.Copy(tileSet.FileName, imagefullpath);
                writer.WriteStartElement("Tiles");
                {
                    foreach (var item in tileSet.ListTiles)
                    {
                        writer.WriteStartElement("Tile");
                        {
                            writer.WriteAttributeString("Id", item.Id.ToString());
                            writer.WriteStartElement("Rect");
                            {
                                writer.WriteAttributeString("X", item.SrcRect.X.ToString());
                                writer.WriteAttributeString("Y", item.SrcRect.Y.ToString());
                            }
                            writer.WriteEndElement();
                        }
                        writer.WriteEndElement();
                    }
                }
                writer.WriteEndElement();
            }
            writer.WriteEndElement();
        }
    }
}