using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml;
using System.IO;

namespace FolderToProject
{
    class Program
    {
        string projectFile;
        string filterFile;
        string unfilteredFile = "";
        int filterPart = 0;

        Program(string targetDir, string projectFileName, string filterFileName)
        {
            DirectoryInfo[] cDirs = new DirectoryInfo(targetDir).GetDirectories();
            string[] fileEntries = Directory.GetFiles(targetDir);

            AddBeginProjectFile();
            AddBeginFilterFile();

            filterFile += "  <ItemGroup>\r\n";
            IterateDirFilters(targetDir, "");
            filterFile += "  </ItemGroup>\r\n";
            filterFile += "  <ItemGroup>\r\n";
            IterateDir(targetDir, "");
            filterFile += unfilteredFile;
            filterFile += "  </ItemGroup>\r\n";

            AddEndProjectFile();
            AddEndFilterFile();

            StreamWriter sw = new StreamWriter(projectFileName, false);
            sw.Write(projectFile);
            sw.Close();
            StreamWriter sw2 = new StreamWriter(filterFileName, false);
            sw2.Write(filterFile);
            sw2.Close();
        }

        void IterateDirFilters(string targetDir, string filterName)
        {
            DirectoryInfo[] directoryEntries = new DirectoryInfo(targetDir).GetDirectories();
            
            foreach (DirectoryInfo s in directoryEntries)
            {
                filterFile += "    <Filter Include=\"" + s.Name + "\">\r\n      <Extensions>cpp;c;cxx;rc;def;r;odl;idl;hpj;bat;h;hpp;hxx;hm;inl</Extensions>\r\n    </Filter>\r\n";
            }
      
            foreach (DirectoryInfo s in directoryEntries)
            {
                if (filterName != "")
                    IterateDirFilters(targetDir + "\\" + s.Name, filterName + "\\" + s.Name);
                else
                    IterateDirFilters(targetDir + "\\" + s.Name, s.Name);
            }
        }

        void IterateDir(string targetDir, string filterName)
        {
            string[] fileEntriesAll = Directory.GetFiles(targetDir);
            List<string> fileEntries = new List<string>();

            foreach (string s in fileEntriesAll)
            {
                if (s.EndsWith(".h") || s.EndsWith(".cpp"))
                {
                    fileEntries.Add(s);
                }
            }
            if (fileEntries.Count > 0)
            {
                // Project file part
                projectFile += "  <ItemGroup>\r\n";
                foreach (string s in fileEntries)
                {
                    projectFile += "   <ClInclude Include=\"" + s + "\" />\r\n";
                }
                projectFile += "  </ItemGroup>\r\n";

                // Filter part
                foreach (string s in fileEntries)
                {
                    if (filterName != "")
                    {
                        filterFile += "    <ClInclude Include=\"" + s + "\">\r\n";
                        filterFile += "      <Filter>" + filterName + "</Filter>\r\n";
                        filterFile += "    </ClInclude>\r\n";
                    }
                    else
                    {
                        unfilteredFile += "    <ClInclude Include=\"" + s + "\" />\r\n";
                    }
                }

                DirectoryInfo[] directoryEntries = new DirectoryInfo(targetDir).GetDirectories();
                foreach (DirectoryInfo s in directoryEntries)
                {
                    if (filterName != "")
                        IterateDir(targetDir + "\\" + s.Name, filterName + "\\" + s.Name);
                    else
                        IterateDir(targetDir + "\\" + s.Name, s.Name);
                }
            }
        }

        static void Main(string[] args)
        {
            new Program(args[0], args[1], args[2]);
        }

        void AddBeginProjectFile()
        {
            StreamReader reader = new StreamReader("projectFileBegin.txt");
            projectFile = reader.ReadToEnd();
            reader.Close();
            projectFile += "\r\n";
        }

        void AddEndProjectFile()
        {
            StreamReader reader = new StreamReader("projectFileEnd.txt");
            projectFile += reader.ReadToEnd();
            reader.Close();
        }

        void AddBeginFilterFile()
        {
            StreamReader reader = new StreamReader("filterFileBegin.txt");
            filterFile = reader.ReadToEnd();
            reader.Close();
            filterFile += "\r\n";
        }

        void AddEndFilterFile()
        {
            StreamReader reader = new StreamReader("filterFileEnd.txt");
            filterFile += reader.ReadToEnd();
            reader.Close();
        }
    }
}
