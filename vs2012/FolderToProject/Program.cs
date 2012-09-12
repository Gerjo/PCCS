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

        Program(string targetDir, string projectFileName, string filterFileName)
        {
            DirectoryInfo[] cDirs = new DirectoryInfo(targetDir).GetDirectories();
            string[] fileEntries = Directory.GetFiles(targetDir);

            AddBeginProjectFile();
            AddBeginFilterFile();

            IterateDir(targetDir, "");

            AddEndProjectFile();
            AddEndFilterFile();

            StreamWriter sw = new StreamWriter(projectFileName, false);
            sw.Write(projectFile);
            sw.Close();
            StreamWriter sw2 = new StreamWriter(filterFileName, false);
            sw2.Write(filterFile);
            sw2.Close();
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
                projectFile += "<ItemGroup>\r\n";
                foreach (string s in fileEntries)
                {
                    projectFile += " <ClInclude Include=\"" + s + "\" />\r\n";
                }
                projectFile += "</ItemGroup>\r\n";

                // Filter part
                filterFile += "<ItemGroup>\r\n";

                foreach (string s in fileEntries)
                {
                    filterFile += "<ClCompile Include=\"" + s + "\">\r\n";
                    if (filterName != "")
                        filterFile += "<Filter>" + filterName + "</Filter>\r\n";
                    filterFile += "</ClCompile>\r\n";
                }

                filterFile += "</ItemGroup>\r\n";

                DirectoryInfo[] directoryEntries = new DirectoryInfo(targetDir).GetDirectories();
                foreach (DirectoryInfo s in directoryEntries)
                {
                    if (filterName != "")
                        IterateDir(s.FullName, filterName + "\\" + s.Name);
                    else
                        IterateDir(s.FullName, s.Name);
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
        }

        void AddEndProjectFile()
        {
            StreamReader reader = new StreamReader("projectFileEnd.txt");
            projectFile += "\r\n";
            projectFile += reader.ReadToEnd();
            reader.Close();
        }

        void AddBeginFilterFile()
        {
            StreamReader reader = new StreamReader("filterFileBegin.txt");
            filterFile = reader.ReadToEnd();
            reader.Close();
        }

        void AddEndFilterFile()
        {
            StreamReader reader = new StreamReader("filterFileEnd.txt");
            filterFile += "\r\n";
            filterFile += reader.ReadToEnd();
            reader.Close();
        }
    }
}
