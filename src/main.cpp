#include <gtk/gtk.h>
#include <math.h>
#include <string>
#include <sstream>
#include <cairo.h>
#include <cmath>
#include <iostream>
#include <string>
#include <cstdio> // for snprintf
#include <cstring> // for strlen
#include <string>
#include <algorithm>

double slider_in_val = 0.0;
double out_val = 0.0;
double param_a = 1.0;
double param_b = 0.0;
int selected_function = 0;

std::string convertCommaToPoint(double value) {
    // Convert the double to a string
    std::string str = std::to_string(value);

    // Replace commas with periods
    std::replace(str.begin(), str.end(), ',', '.');

    return str;
}

// Linear Curve with gradient
double f_linear(double x, double a = 1, double b = 0) {
    return a * x + b;
}

// Exponential Curve with base and scale
double f_exponential(double x, double a = M_E, double b = 1) {
    return b * (std::pow(a, x) - 1);
}

// Logarithmic Curve with base and scale
double f_logarithmic(double x, double a = M_E, double b = 1) {
    return b * (std::log(x + 1) / log(a));
}

// S-Curve (Sigmoid Curve) with steepness and midpoint
double f_s_curve(double x, double a = 1, double b = 0) {
    return 1 / (1 + std::exp(-a * (x - b)));
}

// Parabolic Curve with coefficient and offset
double f_parabolic(double x, double a = 1, double b = 0) {
    return a * std::pow(x, 2) + b;
}

// Cubic Curve with coefficient and offset
double f_cubic(double x, double a = 1, double b = 0) {
    return a * std::pow(x, 3) + b * std::pow(x, 2);
}

// Quadratic Curve with coefficients
double f_quadratic(double x, double a = 1, double b = 0) {
    return a * std::pow(x, 2) + b * x;
}

// Step Curve with number of steps and scale
double f_step(double x, double a = 10, double b = 1) {
    double step_size = 1.0 / a;
    return b * std::floor(x / step_size) * step_size;
}

// Sensitivity Curve with sensitivity level and offset
double f_sensitivity(double x, double a = 2.0, double b = 0) {
    return std::pow(x, a) + b;
}

double evaluate_function(double x,double a = 0, double b = 0) {
    switch (selected_function) {
        case 0:
            return f_linear(x, param_a, param_b);
        case 1:
            return f_exponential(x, param_a, param_b);
        case 2:
            return f_logarithmic(x, param_a, param_b);
        case 3:
            return f_s_curve(x, param_a, param_b);
        case 4:
            return f_parabolic(x, param_a, param_b);
        case 5:
            return f_cubic(x, param_a, param_b);
        case 6:
            return f_quadratic(x, param_a, param_b);
        case 7:
            return f_step(x, param_a, param_b);
        case 8:
            return f_sensitivity(x, param_a, param_b);
        default:
            return 0.0;
    }
}

std::string equation_linear(double a = 1, double b = 0) {
    std::string res=convertCommaToPoint(a) + " * x + " + convertCommaToPoint(b);
    std::cout << res << std::endl;
    return res;
}

std::string equation_exponential(double a = M_E, double b = 1) {
    std::string res=convertCommaToPoint(b) + " * (std::pow(" + convertCommaToPoint(a) + ", x) - 1)";
    return res;
}

std::string equation_logarithmic(double a = M_E, double b = 1) {
    std::string res=convertCommaToPoint(b) + " * (std::log(x + 1) / std::log(" + convertCommaToPoint(a) + "))";
    return res;
}

std::string equation_s_curve(double a = 1, double b = 0) {
    std::string res= "1 / (1 + std::exp(-" + convertCommaToPoint(a) + " * (x - " + convertCommaToPoint(b) + ")))";
    return res;
}

std::string equation_parabolic(double a = 1, double b = 0) {
    std::string res= convertCommaToPoint(a) + " * std::pow(x, 2) + " + convertCommaToPoint(b);
    return res;
}

std::string equation_cubic(double a = 1, double b = 0) {
    std::string res= convertCommaToPoint(a) + " * std::pow(x, 3) + " + convertCommaToPoint(b) + " * std::pow(x, 2)";
    return res;
}

std::string equation_quadratic(double a = 1, double b = 0) {
    std::string res= convertCommaToPoint(a) + " * std::pow(x, 2) + " + convertCommaToPoint(b) + " * x";
    return res;
}

std::string equation_step(double a = 10, double b = 1) {
    std::string res= convertCommaToPoint(b) + " * std::floor(x / (1.0 / " + convertCommaToPoint(a) + ")) * (1.0 / " + convertCommaToPoint(a) + ")";
    return res;
}

std::string equation_sensitivity(double a = 2.0, double b = 0) {
    std::string res= "std::pow(x, " + convertCommaToPoint(a) + ") + " + convertCommaToPoint(b);
    return res;
}

std::string equation_cpp_function(double a = 0, double b = 0) {
    switch (selected_function) {
        case 0:
            return equation_linear( param_a, param_b);
        case 1:
            return equation_exponential( param_a, param_b);
        case 2:
            return equation_logarithmic( param_a, param_b);
        case 3:
            return equation_s_curve( param_a, param_b);
        case 4:
            return equation_parabolic( param_a, param_b);
        case 5:
            return equation_cubic( param_a, param_b);
        case 6:
            return equation_quadratic( param_a, param_b);
        case 7:
            return equation_step( param_a, param_b);
        case 8:
            return equation_sensitivity( param_a, param_b);
        default:
            return "";
    }
}

void on_function_changed(GtkComboBox *combo_box, gpointer data) {
    selected_function = gtk_combo_box_get_active(combo_box);
    GtkWidget *drawing_area = GTK_WIDGET(data);
    gtk_widget_queue_draw(drawing_area);
}

void update_in_val(GtkRange *range, gpointer data) {
    // Update the slider_in_val based on the slider value
    slider_in_val = gtk_range_get_value(GTK_RANGE(range));
    
    // Redraw the graph with the new parameters
    GtkWidget *drawing_area = GTK_WIDGET(data);
    gtk_widget_queue_draw(drawing_area);
}

void update_in_val_set_entry(GtkRange *range, gpointer data) {
    GtkWidget *output_val = GTK_WIDGET(data);
    // Get the current value of the slider

    double value=evaluate_function(slider_in_val, param_a, param_b);
    // Buffer size, make sure it's large enough to hold the formatted string
    char buffer[50];
    
    // Convert double to char* using snprintf
    snprintf(buffer, sizeof(buffer), "%f", value);
    
    // If you need a dynamically allocated char* (e.g., for returning from a function), do this:
    char* cstr = new char[strlen(buffer) + 1];
    std::strcpy(cstr, buffer);
    
    //char *value_str = printf("%.2f", value);
    // Update the entry with the new value
    gtk_entry_set_text(GTK_ENTRY(output_val), cstr);
    // Free the string created by g_strdup_printf
    // g_free(value_str);
    delete[] cstr;
}

// Callback function to update the graph and generated code
void update_param_a(GtkRange *range, gpointer data) {
    // Update the slider_in_val based on the slider value
    param_a = gtk_range_get_value(GTK_RANGE(range));

    // Redraw the graph with the new parameters
    GtkWidget *drawing_area = GTK_WIDGET(data);
    gtk_widget_queue_draw(drawing_area);
}
// Callback function to update the graph and generated code
void update_param_b(GtkRange *range, gpointer data) {
    // Update the slider_in_val based on the slider value
    param_b = gtk_range_get_value(GTK_RANGE(range));

    // Redraw the graph with the new parameters
    GtkWidget *drawing_area = GTK_WIDGET(data);
    gtk_widget_queue_draw(drawing_area);
}

void on_generate_cpp_clicked(GtkButton *button, gpointer data) {
    GtkWidget *cpp_gen_from_equ = GTK_WIDGET(data);
    std::string str= equation_cpp_function( param_a, param_b);
    char* cstr = new char[str.length() + 1]; // +1 for the null terminator
    std::strcpy(cstr, str.c_str());

    gtk_entry_set_text(GTK_ENTRY(cpp_gen_from_equ), cstr);
    delete[] cstr;
}

gboolean on_draw_event(GtkWidget *widget, cairo_t *cr, gpointer user_data) {
    //Background
    cairo_set_source_rgb(cr, 1, 1, 1);
    cairo_paint(cr);

    // Draw the graph
    double width = 400;//gtk_widget_get_allocated_width(widget);
    double height = 400;//gtk_widget_get_allocated_height(widget);

    cairo_translate(cr, width / 2, height / 2);
    //Axis Line
    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_move_to(cr, -width / 2, 0);
    cairo_line_to(cr, width / 2, 0);
    cairo_stroke(cr);

    cairo_move_to(cr, 0, -height / 2);
    cairo_line_to(cr, 0, height / 2);
    cairo_stroke(cr);
    // Equation Line for y = x^2
    cairo_set_source_rgb(cr, 0, 0, 1);
    //cairo_move_to(cr, -width / 2, 0);//(-width / 2) * (-width / 2) / (width / 2));
    for (double x = -1; x <= 1; x += 0.001) {
        double y = evaluate_function(x, param_a, param_b);
        double x_=x*width / 2;
        double y_=-y*(width / 2); //because screen coordinates are inverting
        if(x == -width / 2){
            cairo_move_to(cr, x_, y_);
        }else{
            cairo_line_to(cr, x_, y_);
        }
    }
    cairo_stroke(cr);
    //    g_print("slider_in_val: %f\n", slider_in_val);
    //Point
    cairo_set_source_rgb(cr, 1, 0, 0);
    cairo_arc(cr, slider_in_val*width / 2, -evaluate_function(slider_in_val, param_a, param_b)*(width / 2), 5, 0, 2 * M_PI);
    cairo_fill(cr);

    return FALSE;
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Joystick Graph Tuner");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 600);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);;
    GtkWidget *vbox_left = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    GtkWidget *vbox_right = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    
    GtkWidget *drawing_area = gtk_drawing_area_new();
    gtk_widget_set_size_request(drawing_area, 400, 400);
    g_signal_connect(G_OBJECT(drawing_area), "draw", G_CALLBACK(on_draw_event), NULL);
    
    // Output value
    GtkWidget *label_output = gtk_label_new("Output:");
    GtkWidget *output_val = gtk_entry_new();
    gtk_entry_set_text(GTK_ENTRY(output_val),"");
    gtk_widget_set_size_request(output_val, -1, 20);
    // C++ code from equation
    GtkWidget *label_gen = gtk_label_new("Generated C++ code:");
    GtkWidget *cpp_gen_from_equ = gtk_entry_new();
    gtk_entry_set_text(GTK_ENTRY(cpp_gen_from_equ), "");
    gtk_widget_set_size_request(cpp_gen_from_equ, -1, 80);

    GtkWidget *combo_box = gtk_combo_box_text_new();
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo_box), "Linear");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo_box), "Exponential");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo_box), "Logarithmic");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo_box), "S-Curve");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo_box), "Parabolic");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo_box), "Cubic");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo_box), "Quadratic");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo_box), "Step");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo_box), "Sensitivity");
    gtk_combo_box_set_active(GTK_COMBO_BOX(combo_box), 0);
    g_signal_connect(combo_box, "changed", G_CALLBACK(on_function_changed), drawing_area);

    GtkWidget *button = gtk_button_new_with_label("Generate C++");
    g_signal_connect(button, "clicked", G_CALLBACK(on_generate_cpp_clicked), cpp_gen_from_equ);
    
    // Input Slider
    GtkWidget *label1 = gtk_label_new("Input");
    GtkWidget *hscale1 = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, -1.0, 1.0, 0.001);
    gtk_range_set_value(GTK_RANGE(hscale1), 0.0);
    g_signal_connect(hscale1, "value-changed", G_CALLBACK(update_in_val), drawing_area);
    g_signal_connect(hscale1, "value-changed", G_CALLBACK(update_in_val_set_entry), output_val);
    // Param a Slider
    GtkWidget *label2 = gtk_label_new("Param a");
    GtkWidget *hscale2 = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, -20.0, 20.0, 0.001);
    gtk_range_set_value(GTK_RANGE(hscale2), 0.0);
    g_signal_connect(hscale2, "value-changed", G_CALLBACK(update_param_a), drawing_area);
    g_signal_connect(hscale2, "value-changed", G_CALLBACK(update_in_val_set_entry), output_val);
    // Param b Slider
    GtkWidget *label3 = gtk_label_new("Param b");

    GtkWidget *hscale3 = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, -20.0, 20.0, 0.001);
    gtk_range_set_value(GTK_RANGE(hscale3), 0.0);
    g_signal_connect(hscale3, "value-changed", G_CALLBACK(update_param_b), drawing_area);
    g_signal_connect(hscale3, "value-changed", G_CALLBACK(update_in_val_set_entry), output_val);
    // Layout
    gtk_container_add(GTK_CONTAINER(window), vbox);
    gtk_box_pack_start(GTK_BOX(vbox), drawing_area, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), label_output, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), output_val, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), label_gen, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), cpp_gen_from_equ, FALSE, FALSE, 0);
    gtk_container_add(GTK_CONTAINER(vbox), hbox);
    gtk_box_pack_start(GTK_BOX(hbox), combo_box, TRUE, TRUE, 0);
    gtk_box_pack_end(GTK_BOX(hbox), button, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), label1, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), hscale1, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), label2, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), hscale2, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), label3, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), hscale3, FALSE, FALSE, 0);
    
    /*
    gtk_box_pack_start(GTK_BOX(hbox), vbox_left, FALSE, FALSE, 0);

    gtk_box_pack_start(GTK_BOX(hbox), vbox_right, TRUE, TRUE, 0);
    
    GtkWidget *drawing_area = gtk_drawing_area_new();
    gtk_widget_set_size_request(drawing_area, 400, 400);
    g_signal_connect(G_OBJECT(drawing_area), "draw", G_CALLBACK(on_draw_event), NULL);
    gtk_box_pack_start(GTK_BOX(hbox), vbox_left, FALSE, FALSE, 0);

    

    g_signal_connect(combo_box, "changed", G_CALLBACK(on_function_changed), hbox);

    GtkWidget *vbox_right = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_box_pack_start(GTK_BOX(hbox), vbox_right, TRUE, TRUE, 0);

    GtkWidget *drawing_area = gtk_drawing_area_new();
    gtk_widget_set_size_request(drawing_area, 400, 400);
    g_signal_connect(G_OBJECT(drawing_area), "draw", G_CALLBACK(on_draw_event), NULL);
    gtk_box_pack_start(GTK_BOX(vbox_right), drawing_area, TRUE, TRUE, 0);


    gtk_box_pack_start(GTK_BOX(vbox_right), entry, FALSE, FALSE, 0);

    

    


    */
    gtk_widget_show_all(window);
    gtk_main();
   
    return 0;
}

