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
        string projectFile = "";
        string filterFile = "";
        string unfilteredFile = "";

        Program(string targetSourceDirectory, string projectFileName)
        {
            projectFile = ReadFile(".\\vs2012\\FolderToProject\\projectFileBegin.txt");
            filterFile = ReadFile(".\\vs2012\\FolderToProject\\filterFileBegin.txt");

            filterFile += "  <ItemGroup>\r\n";
            IterateDirFilters(targetSourceDirectory, "");
            filterFile += "  </ItemGroup>\r\n";
            filterFile += "  <ItemGroup>\r\n";
            IterateDir(targetSourceDirectory, "");
            filterFile += unfilteredFile;
            filterFile += "  </ItemGroup>\r\n";

            projectFile += ReadFile(".\\vs2012\\FolderToProject\\projectFileEnd.txt");
            filterFile += ReadFile(".\\vs2012\\FolderToProject\\filterFileEnd.txt");

            StreamWriter projectStreamWriter = new StreamWriter(projectFileName, false);
            projectStreamWriter.Write(projectFile);
            projectStreamWriter.Close();

            StreamWriter filterStreamWriter = new StreamWriter(projectFileName + ".filters", false);
            filterStreamWriter.Write(filterFile);
            filterStreamWriter.Close();
        }

        string ReadFile(string readFile)
        {
            StreamReader reader = new StreamReader(readFile);
            string temp = reader.ReadToEnd();
            temp += "\r\n";
            reader.Close();
            return temp;
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
                    projectFile += "   <ClCompile Include=\"" + s + "\" />\r\n";
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
            new Program(args[0], args[1]);
        }
    }
}
