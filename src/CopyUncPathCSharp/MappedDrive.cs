using System.Runtime.InteropServices;
using System.IO;
using System.Text;

namespace CopyPathToClipboard
{
    public class MappedDrive
    {
        //The Win32 API needed
        [DllImport("mpr.dll", CharSet = CharSet.Unicode, SetLastError = true)]
        public static extern int WNetGetConnection([MarshalAs(UnmanagedType.LPTStr)] string localName, 
            [MarshalAs(UnmanagedType.LPTStr)] StringBuilder remoteName, ref int length);

        /// <summary>
        /// method for retrieving the UNC path for all mapped drives
        /// </summary>
        /// <returns>a generic list of MappedDrive</returns>
        public static string GetUncPath(string path)
        {
            if (path.Substring(0, 2) == "\\") return path;

            foreach (var drive in DriveInfo.GetDrives())
            {
                if (drive.Name.Substring(0, 3) != path.Substring(0, 3)) continue;
                if (drive.DriveType.Equals(DriveType.Network))
                {
                    var path1 = new StringBuilder(255);
                    //capacity of the string builder (required for the Win32 API call)
                    var len = path1.Capacity;
                    WNetGetConnection(drive.Name.Replace("\\", ""), path1, ref len);
                    return path.Replace(path.Substring(0, 2), path1.ToString());
                }
                    
                return path;
            }
            
            return path;
        }
    }
}
