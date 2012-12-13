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

        Program(string[] args, string projectFileName)
        {
            string[] targetSourceDirectory = new string[args.Length - 1];
            for (int i = 0; i < args.Length - 1; ++i)
            {
                targetSourceDirectory[i] = args[i];
            }
            

            int index = projectFileName.LastIndexOf('\\');
            string path = projectFileName.Remove(index);

            projectFile = ReadFile(path + "\\pf0.xml");
            filterFile = ReadFile("filterFileBegin.txt");

            filterFile += "  <ItemGroup>\r\n";
            foreach (string s in targetSourceDirectory)
            {
                IterateDirFilters(s, "");
            }
            filterFile += "  </ItemGroup>\r\n";
            filterFile += "  <ItemGroup>\r\n";
            foreach (string s in targetSourceDirectory)
            {
                IterateDir(s, "");
            }
            filterFile += unfilteredFile;
            filterFile += "  </ItemGroup>\r\n";

            projectFile += ReadFile(path + "\\pf1.xml");
            filterFile += ReadFile("filterFileEnd.txt");

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
                String combinedName = filterName + s.Name;
                combinedName = combinedName.Replace("\\\\", "\\");
                filterFile += "    <Filter Include=\"" + combinedName + "\">\r\n      <Extensions>cpp;c;cc;cxx;def;odl;idl;hpj;bat;asm;asmx;h;hpp;hxx;hm;inl;inc;xsd</Extensions>\r\n    </Filter>\r\n";
            }

            foreach (DirectoryInfo s in directoryEntries)
            {
                if (filterName != "")
                    IterateDirFilters(targetDir + "\\" + s.Name, filterName + "\\" + s.Name + "\\");
                else
                    IterateDirFilters(targetDir + "\\" + s.Name, s.Name + "\\");
            }
        }

        void IterateDir(string targetDir, string filterName)
        {
            string[] fileEntriesAll = Directory.GetFiles(targetDir);
            List<string> fileEntries = new List<string>();

            foreach (string s in fileEntriesAll)
            {
                if (s.EndsWith(".h") || s.EndsWith(".cpp") || s.EndsWith(".inl"))
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
                    if (s.EndsWith(".h") || s.EndsWith(".inl"))
                        projectFile += "   <ClInclude Include=\"" + s + "\" />\r\n";
                    else
                        projectFile += "   <ClCompile Include=\"" + s + "\" />\r\n";
                }
                projectFile += "  </ItemGroup>\r\n";

                // Filter part
                foreach (string s in fileEntries)
                {
                    if (filterName != "")
                    {
                        if (s.EndsWith(".h") || s.EndsWith(".inl"))
                        {
                            filterFile += "    <ClInclude Include=\"" + s + "\">\r\n";
                            filterFile += "      <Filter>" + filterName + "</Filter>\r\n";
                            filterFile += "    </ClInclude>\r\n";
                        }
                        else
                        {
                            filterFile += "    <ClCompile Include=\"" + s + "\">\r\n";
                            filterFile += "      <Filter>" + filterName + "</Filter>\r\n";
                            filterFile += "    </ClCompile>\r\n";
                        }
                    }
                    else
                    {
                        if (s.EndsWith(".h") || s.EndsWith(".inl"))
                            unfilteredFile += "    <ClInclude Include=\"" + s + "\" />\r\n";
                        else
                            unfilteredFile += "    <ClCompile Include=\"" + s + "\" />\r\n";
                    }
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

        static void Main(string[] args)
        {
            if (args.Length == 0)
            {
                System.Console.WriteLine("Syntax: \"src\" \"src\" \"projectfile\"");
                System.Console.ReadLine();
            }
            else
            {
                new Program(args, args[args.Length - 1]);
            }
        }
    }
}
