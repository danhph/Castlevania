using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml;

namespace MapEditor.Tiles
{
    internal class TileMap
    {
        private readonly int[,] _matrixIndex;

        public TileMap(int column, int row)
        {
            Column = column;
            Row = row;
            _matrixIndex = new int[column, row];
            TileSet = null;
            ListObject = new List<GameObject>();
        }

        public int this[int i, int j]
        {
            get { return _matrixIndex[i, j]; }
            set { _matrixIndex[i, j] = value; }
        }

        public int Column { get; }

        public TileSet TileSet { get; set; }
        public int Row { get; }
        public List<GameObject> ListObject { get; set; }

        public static void Save(TileMap tileMap, string path)
        {
            using (var wr = new XmlTextWriter(path, Encoding.UTF8))
            {
                wr.Formatting = Formatting.Indented;
                wr.WriteStartDocument();
                wr.WriteStartElement("TileMap");
                {
                    wr.WriteAttributeString("Column", tileMap.Column.ToString());
                    wr.WriteAttributeString("Row", tileMap.Row.ToString());

                    wr.WriteStartElement("MatrixIndex");
                    {
                        for (var i = 0; i < tileMap.Row; i++)
                        {
                            wr.WriteStartElement("Row");
                            {
                                wr.WriteAttributeString("id", i.ToString());
                                for (var j = 0; j < tileMap.Column; j++)
                                {
                                    wr.WriteString(tileMap[j, i].ToString());
                                    if (j != tileMap.Column - 1)
                                        wr.WriteString("\t");
                                }
                            }
                            wr.WriteEndElement();
                        }
                    }
                    wr.WriteEndElement();
                    if (tileMap.TileSet != null)
                        TileSet.Save(wr, tileMap.TileSet, path);
                    if (tileMap.ListObject.Any())
                        GameObject.Save(wr, tileMap.ListObject, path);
                }
                wr.WriteEndElement();
                wr.WriteEndDocument();
                wr.Close();
                wr.Dispose();
            }
        }
    }
}