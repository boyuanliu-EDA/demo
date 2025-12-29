#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <iostream>
#include <sstream>

struct ClockGatingCell {
    std::string cell_name;
    std::string enable_pin;
    std::string clock_pin;
    
    // rst 的5个值
    double min_rise;       // 对应 hold (rise)
    double min_fall;       // 对应 hold (fall)
    double max_rise;       // 对应 setup (rise)
    double max_fall;       // 对应 setup (fall)
    std::string high_or_low;  // 对应 High/Low
    std::string attr;      // 对应 Attr
};

// 主要报告函数
void report_clock_gating_check(const std::vector<ClockGatingCell>& cells) {
    // 定义列宽
    const int col_cell = 6;      // Cell
    const int col_enable = 8;    // Enable
    const int col_clock = 8;     // Clock
    const int col_group = 20;    // Rise/Fall 组的宽度 (Setup + Hold)
    const int col_setup = 10;    // Setup 列的宽度
    const int col_hold = 10;     // Hold 列的宽度
    const int col_hl = 10;       // High/Low
    const int col_attr = 6;      // Attr
    
    const int total_width = col_cell + col_enable + col_clock + 
                           (col_setup + col_hold) * 2 + 
                           col_hl + col_attr + 4;  // 额外间距
    
    // 打印表头
    std::cout << std::string(total_width, '-') << std::endl;
    
    // 第一行：Rise 和 Fall 居中显示
    std::cout << std::left;
    
    // 前三个列：Cell, Enable, Clock
    std::cout << std::setw(col_cell + col_enable + col_clock) << "";
    
    // Rise 组 (居中显示)
    int rise_group_width = col_setup + col_hold;
    int rise_padding = (rise_group_width - 4) / 2;  // "Rise" 长度是4
    
    std::cout << std::right;
    std::cout << std::setw(rise_padding + 4) << "Rise";
    std::cout << std::left;
    
    // Fall 组 (居中显示)
    int fall_group_width = col_setup + col_hold;
    int fall_padding = (fall_group_width - 4) / 2;
    
    std::cout << std::right;
    std::cout << std::setw(fall_padding + 4 + col_hl) << "Fall";
    std::cout << std::left;
    
    std::cout << std::endl;
    
    // 第二行：详细的列标题
    std::cout << std::setw(col_cell) << "Cell";
    std::cout << std::setw(col_enable) << "Enable";
    std::cout << std::setw(col_clock) << "Clock";
    
    // Rise 下面的 Setup 和 Hold
    std::cout << std::setw(col_setup) << "Setup";
    std::cout << std::setw(col_hold) << "Hold";
    
    // Fall 下面的 Setup 和 Hold
    std::cout << std::setw(col_setup) << "Setup";
    std::cout << std::setw(col_hold) << "Hold";
    
    // 最后的列
    std::cout << std::setw(col_hl) << "High/Low";
    std::cout << std::setw(col_attr) << "Attr";
    
    std::cout << std::endl;
    std::cout << std::string(total_width, '-') << std::endl;
    
    // 打印数据行
    for (const auto& cell : cells) {
        // 前三列文本
        std::cout << std::left;
        std::cout << std::setw(col_cell) << cell.cell_name;
        std::cout << std::setw(col_enable) << cell.enable_pin;
        std::cout << std::setw(col_clock) << cell.clock_pin;
        
        // Rise Setup (右对齐)
        std::cout << std::right << std::fixed << std::setprecision(2);
        std::cout << std::setw(col_setup - 2) << cell.max_rise << " *";
        
        // Rise Hold (右对齐)
        std::cout << std::setw(col_hold - 2) << cell.min_rise << " *";
        
        // Fall Setup (右对齐)
        std::cout << std::setw(col_setup - 2) << cell.max_fall << " *";
        
        // Fall Hold (右对齐)
        std::cout << std::setw(col_hold - 2) << cell.min_fall << " *";
        
        // 最后两列文本
        std::cout << std::left;
        std::cout << std::setw(col_hl) << cell.high_or_low;
        std::cout << std::setw(col_attr) << cell.attr;
        
        std::cout << std::endl;
    }
    
    std::cout << std::string(total_width, '-') << std::endl;
}

// 更精确的版本，确保 Rise/Fall 正好在 Setup 和 Hold 的正中间
void report_clock_gating_check_precise(const std::vector<ClockGatingCell>& cells) {
    // 精确计算列宽
    const int col_widths[] = {6, 7, 7, 9, 9, 9, 9, 9, 5};
    const char* headers[] = {"Cell", "Enable", "Clock", "Setup", "Hold", "Setup", "Hold", "High/Low", "Attr"};
    
    const int num_cols = sizeof(col_widths) / sizeof(col_widths[0]);
    int total_width = 0;
    for (int i = 0; i < num_cols; i++) {
        total_width += col_widths[i];
    }
    
    std::cout << std::string(total_width, '-') << std::endl;
    
    // 第一行：Rise 和 Fall 居中
    // 计算 Rise 和 Fall 的位置
    int rise_start = col_widths[0] + col_widths[1] + col_widths[2];  // Cell + Enable + Clock
    int rise_width = col_widths[3] + col_widths[4];  // Setup + Hold
    
    int fall_start = rise_start + rise_width;
    int fall_width = col_widths[5] + col_widths[6];  // Setup + Hold
    
    // 打印第一行
    std::cout << std::left;
    std::cout << std::setw(rise_start) << "";
    
    // 打印 Rise (居中)
    int rise_center = rise_start + rise_width/2 - 2;  // "Rise" 长度是4
    std::cout << std::right;
    std::cout << std::setw(rise_center) << "";
    std::cout << "Rise";
    
    // 打印 Fall (居中)
    int fall_center = fall_start + fall_width/2 - 2;
    std::cout << std::setw(fall_center - rise_center - 4) << "";
    std::cout << "Fall";
    
    std::cout << std::endl;
    
    // 第二行：详细的列标题
    std::cout << std::left;
    for (int i = 0; i < num_cols; i++) {
        std::cout << std::setw(col_widths[i]) << headers[i];
    }
    std::cout << std::endl;
    
    std::cout << std::string(total_width, '-') << std::endl;
    
    // 打印数据行
    for (const auto& cell : cells) {
        // Cell, Enable, Clock
        std::cout << std::left;
        std::cout << std::setw(col_widths[0]) << cell.cell_name;
        std::cout << std::setw(col_widths[1]) << cell.enable_pin;
        std::cout << std::setw(col_widths[2]) << cell.clock_pin;
        
        // 数值列（右对齐）
        std::cout << std::right << std::fixed << std::setprecision(2);
        
        // Rise Setup
        std::cout << std::setw(col_widths[3] - 2) << cell.max_rise << " *";
        
        // Rise Hold
        std::cout << std::setw(col_widths[4] - 2) << cell.min_rise << " *";
        
        // Fall Setup
        std::cout << std::setw(col_widths[5] - 2) << cell.max_fall << " *";
        
        // Fall Hold
        std::cout << std::setw(col_widths[6] - 2) << cell.min_fall << " *";
        
        // High/Low 和 Attr
        std::cout << std::left;
        std::cout << std::setw(col_widths[7]) << cell.high_or_low;
        std::cout << std::setw(col_widths[8]) << cell.attr;
        
        std::cout << std::endl;
    }
    
    std::cout << std::string(total_width, '-') << std::endl;
}

// 使用字符串操作确保精确对齐
void report_clock_gating_check_exact(const std::vector<ClockGatingCell>& cells) {
    // 精确的列配置
    struct Column {
        std::string name;
        int width;
        bool is_numeric;
    };
    
    std::vector<Column> columns = {
        {"Cell", 6, false},
        {"Enable", 7, false},
        {"Clock", 7, false},
        {"Setup", 9, true},   // Rise Setup
        {"Hold", 9, true},    // Rise Hold  
        {"Setup", 9, true},   // Fall Setup
        {"Hold", 9, true},    // Fall Hold
        {"High/Low", 9, false},
        {"Attr", 5, false}
    };
    
    // 计算总宽度
    int total_width = 0;
    for (const auto& col : columns) {
        total_width += col.width;
    }
    
    // 打印表格边框
    std::cout << std::string(total_width, '-') << std::endl;
    
    // 第一行：Rise 和 Fall 居中
    std::string header_line1;
    
    // 前三列空白
    int prefix_width = columns[0].width + columns[1].width + columns[2].width;
    header_line1.append(prefix_width, ' ');
    
    // Rise 组 (居中)
    int rise_group_start = prefix_width;
    int rise_group_width = columns[3].width + columns[4].width;
    int rise_pos = rise_group_start + (rise_group_width - 4) / 2;  // 4是"Rise"的长度
    
    header_line1.append(rise_pos - prefix_width, ' ');
    header_line1 += "Rise";
    
    // Fall 组 (居中)
    int fall_group_start = rise_group_start + rise_group_width;
    int fall_group_width = columns[5].width + columns[6].width;
    int fall_pos = fall_group_start + (fall_group_width - 4) / 2;  // 4是"Fall"的长度
    
    header_line1.append(fall_pos - (rise_pos + 4), ' ');
    header_line1 += "Fall";
    
    std::cout << header_line1 << std::endl;
    
    // 第二行：列标题
    std::cout << std::left;
    for (const auto& col : columns) {
        std::cout << std::setw(col.width) << col.name;
    }
    std::cout << std::endl;
    
    std::cout << std::string(total_width, '-') << std::endl;
    
    // 打印数据行
    for (const auto& cell : cells) {
        std::ostringstream line;
        
        // 前三列文本
        line << std::left;
        line << std::setw(columns[0].width) << cell.cell_name;
        line << std::setw(columns[1].width) << cell.enable_pin;
        line << std::setw(columns[2].width) << cell.clock_pin;
        
        // 数值列
        line << std::right << std::fixed << std::setprecision(2);
        
        // Rise Setup
        line << std::setw(columns[3].width - 2) << cell.max_rise << " *";
        
        // Rise Hold
        line << std::setw(columns[4].width - 2) << cell.min_rise << " *";
        
        // Fall Setup
        line << std::setw(columns[5].width - 2) << cell.max_fall << " *";
        
        // Fall Hold
        line << std::setw(columns[6].width - 2) << cell.min_fall << " *";
        
        // 最后两列
        line << std::left;
        line << std::setw(columns[7].width) << cell.high_or_low;
        line << std::setw(columns[8].width) << cell.attr;
        
        std::cout << line.str() << std::endl;
    }
    
    std::cout << std::string(total_width, '-') << std::endl;
}

int main() {
    // 示例数据（使用你提供的值）
    std::vector<ClockGatingCell> cells = {
        {"c1", "B", "A", 0.07, 0.07, 0.04, 0.04, "High", "I"},
        {"c2", "B", "A", 0.07, 0.07, 0.04, 0.04, "High", "I"}
    };
    
    std::cout << "Clock Gating Check Report:" << std::endl;
    std::cout << "==========================" << std::endl;
    
    std::cout << "\nVersion 1:" << std::endl;
    report_clock_gating_check(cells);
    
    std::cout << "\n\nVersion 2 (precise):" << std::endl;
    report_clock_gating_check_precise(cells);
    
    std::cout << "\n\nVersion 3 (exact alignment):" << std::endl;
    report_clock_gating_check_exact(cells);
    
    return 0;
}