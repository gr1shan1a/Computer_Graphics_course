#include <gtk/gtk.h>
#include <math.h>

double scale = 1.0;  // Начальный масштаб

GtkWidget *drawing_area;

double x1 = 100.0;
double start_y1 = 30.0;
double x2 = 50.0;
double y2 = 200.0;
double x3 = 150.0;
double y3 = 140.0;



void scaling(double *a1, double *b1, double *a2, double *b2, double *a3, double *b3 , double scale) {
    double m1 = *a1;
    double m2 = *a2;
    double m3 = *a3;
    double n1 = *b1;
    double n2 = *b2;
    double n3 = *b3;

    double Xcenter = (m1 + m2 + m3) / 3.0;
    double Ycenter = (n1 + n2 + n3) / 3.0;

    double newX1, newY1, newX2, newY2 , newX3, newY3;

    if (scale == 1.0)
        return;
    if (scale < 0.1) {
        scale = 0.1;
    } else {


        newX1 = Xcenter + (m1 - Xcenter) * scale;
        newY1 = Ycenter + (n1 - Ycenter) * scale;

        newX2 = Xcenter + (m2 - Xcenter) * scale;
        newY2 = Ycenter + (n2 - Ycenter) * scale;

        newX3 = Xcenter + (m3 - Xcenter) * scale;
        newY3 = Ycenter + (n3 - Ycenter) * scale;
    }

    *a1 = newX1;
    *b1 = newY1;
    *a2 = newX2;
    *b2 = newY2;
    *a3 = newX3;
    *b3 = newY3;
}



void rotate(double *a1, double *b1, double *a2, double *b2, double *a3, double *b3, double angle) {

    double z1 = *a1;
    double z2 = *a2;
    double c1 = *b1;
    double c2 = *b2;
    double z3 = *a3;
    double c3 = *b3;

    double Xcenter = (double)((z1 + z2 + z3) / 3.0);
    double Ycenter = (double)((c1 + c2 + c3) / 3.0);

    double cos_angle = cos(angle);
    double sin_angle = sin(angle);


    double newX1, newY1, newX2, newY2, newX3, newY3;


    newX1 = Xcenter + (z1 - Xcenter) * cos_angle - (c1 - Ycenter) * sin_angle;
    newY1 = Ycenter + (z1 - Xcenter) * sin_angle + (c1 - Ycenter) * cos_angle;

    newX2 = Xcenter + (z2 - Xcenter) * cos_angle - (c2 - Ycenter) * sin_angle;
    newY2 = Ycenter + (z2 - Xcenter) * sin_angle + (c2 - Ycenter) * cos_angle;

    newX3 = Xcenter + (z3 - Xcenter) * cos_angle - (c3 - Ycenter) * sin_angle;
    newY3 = Ycenter + (z3 - Xcenter) * sin_angle + (c3 - Ycenter) * cos_angle;


    *a1 = (double)newX1;
    *b1 = (double)newY1;
    *a2 = (double)newX2;
    *b2 = (double)newY2;
    *a3 = (double)newX3;
    *b3 = (double)newY3;
}



static gboolean on_key_press(GtkWidget *widget, GdkEventKey *event, gpointer user_data, cairo_t *cr) {
    switch (event->keyval) {
        case GDK_KEY_Control_L:
            scale -= 0.1;
            if (scale < 0.1) scale = 0.1;  // Prevent scale from going below 0.1
            scaling(&x1, &start_y1, &x2, &y2, &x3, &y3, scale);
            cairo_move_to(cr, x1, start_y1);
            cairo_line_to(cr, x2, y2);
            cairo_move_to(cr, x2, y2);
            cairo_line_to(cr, x3, y3);
            cairo_move_to(cr, x3, y3);
            cairo_line_to(cr, x1, start_y1);
            cairo_stroke(cr);
            break;
        case GDK_KEY_Tab:
            scale += 0.1;
            scaling(&x1, &start_y1, &x2, &y2, &x3, &y3, scale);
            cairo_move_to(cr, x1, start_y1);
            cairo_line_to(cr, x2, y2);
            cairo_move_to(cr, x2, y2);
            cairo_line_to(cr, x3, y3);
            cairo_move_to(cr, x3, y3);
            cairo_line_to(cr, x1, start_y1);
            cairo_stroke(cr);
            break;

        case GDK_KEY_a:
            x1 -= 10.0;
            x2 -= 10.0;
            x3 -= 10.0;
            cairo_move_to(cr, x1, start_y1);
            cairo_line_to(cr, x2, y2);
            cairo_move_to(cr, x2, y2);
            cairo_line_to(cr, x3, y3);
            cairo_move_to(cr, x3, y3);
            cairo_line_to(cr, x1, start_y1);
            cairo_stroke(cr);
            break;
        case GDK_KEY_d:
            x1 += 10.0;
            x2 += 10.0;
            x3 += 10.0;
            cairo_move_to(cr, x1, start_y1);
            cairo_line_to(cr, x2, y2);
            cairo_move_to(cr, x2, y2);
            cairo_line_to(cr, x3, y3);
            cairo_move_to(cr, x3, y3);
            cairo_line_to(cr, x1, start_y1);
            cairo_stroke(cr);
            break;
        case GDK_KEY_s:
            start_y1 += 10.0;
            y2 += 10.0;
            y3 += 10.0;
            cairo_move_to(cr, x1, start_y1);
            cairo_line_to(cr, x2, y2);
            cairo_move_to(cr, x2, y2);
            cairo_line_to(cr, x3, y3);
            cairo_move_to(cr, x3, y3);
            cairo_line_to(cr, x1, start_y1);
            cairo_stroke(cr);
            break;
        case GDK_KEY_w:
            start_y1 -= 10.0;
            y2 -= 10.0;
            y3 -= 10.0;
            cairo_move_to(cr, x1, start_y1);
            cairo_line_to(cr, x2, y2);
            cairo_move_to(cr, x2, y2);
            cairo_line_to(cr, x3, y3);
            cairo_move_to(cr, x3, y3);
            cairo_line_to(cr, x1, start_y1);
            cairo_stroke(cr);
            break;

        case GDK_KEY_q:
            rotate(&x1, &start_y1, &x2, &y2, &x3, &y3,  -0.1); // Поворот на -0.1 радиан
            gtk_widget_queue_draw(drawing_area);
            break;
        case GDK_KEY_e:
            rotate(&x1, &start_y1, &x2, &y2, &x3, &y3, 0.1);  // Поворот на 0.1 радиан
            gtk_widget_queue_draw(drawing_area);
            break;

        default:
            return FALSE;  // Не обрабатывать другие клавиши
    }

    gtk_widget_queue_draw(drawing_area);
    return TRUE;
}


static void draw(GtkWidget *widget, cairo_t *cr, gpointer data) {
    // Set line color to black
    cairo_set_source_rgb(cr, 0, 0, 0);

    // Set line width
    cairo_set_line_width(cr, 3.0);

    // Draw a line from (10, 10) to (100, 100)
    cairo_move_to(cr, x1, start_y1);
    cairo_line_to(cr, x2, y2);
    cairo_move_to(cr, x2, y2);
    cairo_line_to(cr, x3, y3);
    cairo_move_to(cr, x3, y3);
    cairo_line_to(cr, x1, start_y1);

    cairo_set_source_rgb(cr, 1, 0, 0.5);

    cairo_stroke(cr);
}

static gboolean on_draw_event(GtkWidget *widget, cairo_t *cr, gpointer data) {
    draw(widget, cr, data);
    return FALSE;
}

static void activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *darea;
    GtkWidget *button;
    GtkWidget *builder;

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Something beautiful <3");
    gtk_window_set_default_size(GTK_WINDOW(window), 500, 500);

    darea = gtk_drawing_area_new();
    gtk_container_add(GTK_CONTAINER (window), darea);

    drawing_area = darea;

    g_signal_connect(G_OBJECT(darea), "draw", G_CALLBACK(on_draw_event), NULL);
    g_signal_connect(G_OBJECT(window), "key-press-event", G_CALLBACK(on_key_press), NULL);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);


    gtk_widget_show_all(window);
}

int main(int argc, char **argv) {
    GtkApplication *app;
    int status;

    app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}
