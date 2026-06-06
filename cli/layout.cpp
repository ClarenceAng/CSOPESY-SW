#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include "process.h"

using String = std::string;

// column border variable logic
static const size_t C1 = 41, C2 = 24, C3 = 22;     // summary column widths
static const size_t W    = C1 + 1 + C2 + 1 + C3;   // inner width = 89
static const size_t SEP1 = C1;                      // 1st separator column (41)
static const size_t SEP2 = C1 + 1 + C2;            // 2nd separator column (66)

// helper functions to fit text into columns appropriately

// Fit the string into the column width. If the string is too long, keep the last couple of 
// characters of the string and prefix "..."
static String fit(const String& s, size_t w) {
    if (s.size() <= w){
        return s + String(w - s.size(), ' ');  // short -> pad right
    } 
    if (w <= 3){
        return s.substr(s.size() - w);         // tiny column -> tail
    }   
    return "..." + s.substr(s.size() - (w - 3));  // long -> "...tail"
}

// Put text into a line, left-anchored at column pos
static void put(String& line, size_t pos, const String& t) {
    for (size_t i = 0; i < t.size() && pos + i < line.size(); ++i){
        line[pos + i] = t[i];
    }
}

// Put text into a line so it ends just before column endPos (right-anchored)
static void putRight(String& line, size_t endPos, const String& t) {
    if (t.size() >= endPos){
        put(line, 0, t);
    } 
    else{
        put(line, endPos - t.size(), t);
    }   
}

// Print a finished W-wide line wrapped in the outer borders
static void printRow(const String& line) {
    std::cout << "|" << line << "|\n";
}

// A blank summary box line with the two column separators already in place
static String gpuCanvas() {
    String line(W, ' ');
    line[SEP1] = '|';
    line[SEP2] = '|';
    return line;
}

int main() {
    // ---- GPU dummy data ----
    int    gpuID         = 0;
    String gpuName       = "NVIDIA GeForce RTX 3050";
    String operatingMode = "WDDM";
    String temperature   = "37C";
    String performance   = "P8";
    String usage         = "11W";
    String capacity      = "180W";
    String busId         = "00000000:26:00.0";
    String dispA         = "On";
    String memoryUsage   = "880MiB /   4096MiB";
    String volatileECC   = "N/A";
    String computeM      = "Default";
    String migM          = "N/A";
    String fanStr        = "28%";
    String utilStr       = "29%";

    // ---- Borders / dividers ----
    String topBorder    = "+" + String(W, '-') + "+";
    String lightDiv     = "+" + String(C1, '-') + "+" + String(C2, '-') + "+" + String(C3, '-') + "+";
    String heavyDiv     = "|" + String(C1, '=') + "+" + String(C2, '=') + "+" + String(C3, '=') + "|";
    String botBorder    = "+" + String(C1, '-') + "+" + String(C2, '-') + "+" + String(C3, '-') + "+";
    String heavyDivFull = "|" + String(W, '=') + "|";

    // ---- Timestamp header (real current time, like nvidia-smi) ----
    std::time_t now = std::time(nullptr);
    char dateBuf[64];
    std::strftime(dateBuf, sizeof(dateBuf), "%a %b %d %H:%M:%S %Y", std::localtime(&now));
    std::cout << dateBuf << "\n";

    // ---- GPU summary box ----
    std::cout << topBorder << "\n";

    // version banner
    String c = String(W, ' ');                                   
    put(c, 1,  "NVIDIA-SMI 551.86");
    put(c, 33, "Driver Version: 551.86");
    putRight(c, W - 1, "CUDA Version: 12.4");
    printRow(c);

    std::cout << lightDiv << "\n";

    // header row 1
    c = gpuCanvas();                                             
    put(c, 1, "GPU  Name"); 
    putRight(c, 40, "TCC/WDDM");
    put(c, 43, "Bus-Id");   
    putRight(c, 65, "Disp.A");
    put(c, 68, "Volatile Uncorr. ECC");
    printRow(c);

    // header row 2
    c = gpuCanvas();                                             
    put(c, 1, "Fan  Temp  Perf"); 
    putRight(c, 40, "Pwr:Usage/Cap");
    putRight(c, 65, "Memory-Usage");
    put(c, 68, "GPU-Util  Compute M.");
    printRow(c);

    // header row 3
    c = gpuCanvas();                                            
    putRight(c, W - 1, "MIG M.");
    printRow(c);

    std::cout << heavyDiv << "\n";

    // data row 1
    c = gpuCanvas();                                             
    put(c, 1, "  " + std::to_string(gpuID) + "  " + gpuName); 
    putRight(c, 40, operatingMode);
    put(c, 43, busId); putRight(c, 65, dispA);
    putRight(c, W - 1, volatileECC);
    printRow(c);

    // data row 2
    c = gpuCanvas();                                             
    put(c, 1, fanStr + "   " + temperature + "   " + performance);
    putRight(c, 40, usage + " / " + capacity);
    putRight(c, 65, memoryUsage);
    put(c, 68, utilStr); putRight(c, W - 1, computeM);
    printRow(c);

    // data row 3
    c = gpuCanvas();                                             
    putRight(c, W - 1, migM);
    printRow(c);

    std::cout << botBorder << "\n\n";


    // 5 dummy data processes
    std::vector<Process> processes = {
        Process(0, "N/A", "N/A", 1368, "C+G", "C:\\Windows\\System32\\dwm.exe", "N/A"),
        Process(0, "N/A", "N/A", 2116, "C+G", "C:\\Program Files\\WindowsApps\\Microsoft.GamingApp_8wekyb3d8bbwe\\XboxGameBarWidgets.exe", "112MiB"),
        Process(0, "N/A", "N/A", 4220, "C+G", "C:\\Program Files (x86)\\Microsoft\\EdgeWebView\\Application\\123.0.2420.65\\msedgewebview2.exe", "78MiB"),
        Process(0, "N/A", "N/A", 5684, "C+G", "C:\\Windows\\explorer.exe", "45MiB"),
        Process(0, "N/A", "N/A", 6676, "C+G", "C:\\Windows\\SystemApps\\Microsoft.Windows.StartMenuExperienceHost_cw5n1h2txyewy\\StartMenuExperienceHost.exe", "60MiB"),
    };

    std::cout << topBorder << "\n";

    // title
    c = String(W, ' '); put(c, 1, "Processes:"); 
    printRow(c);   

    // header line 1
    c = String(W, ' ');                                         
    put(c, 2, "GPU"); put(c, 8, "GI"); put(c, 14, "CI"); putRight(c, 26, "PID");
    put(c, 31, "Type"); put(c, 38, "Process name"); putRight(c, W - 1, "GPU Memory");
    printRow(c);

    // header line 2
    c = String(W, ' ');                                         
    put(c, 8, "ID"); put(c, 14, "ID"); putRight(c, W - 1, "Usage");
    printRow(c);

    std::cout << heavyDivFull << "\n";

    const size_t NAME_W = 40; // long names beyond this cap get the "..." prefix treatment
    for (const Process& p : processes) {
        c = String(W, ' ');
        putRight(c, 6,  std::to_string(p.getGpuID()));
        put(c, 8,  p.getGiID());
        put(c, 14, p.getCiID());
        putRight(c, 26, std::to_string(p.getPid()));
        put(c, 31, p.getType());
        put(c, 38, fit(p.getName(), NAME_W)); // <-- trunc happens here
        putRight(c, W - 1, p.getGpuMemoryUsage());
        printRow(c);
    }

    std::cout << topBorder << "\n";
    return 0;
}
