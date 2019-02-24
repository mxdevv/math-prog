#ifndef GTK_C
#define GTK_C

#include <string.h>
#include <gtk/gtk.h>

#include "variant.c"
#include "util.c"
#include "func_parser.c"

GtkWidget *window;

GtkWidget *calc_btn;
GtkWidget *exit_btn;
GtkWidget *combo_variant;
GtkWidget *combo_lab_work;
GtkWidget *combo_method;
GtkWidget *scale_eps;
GtkWidget *scale_lambda;
GtkWidget *scale_low;
GtkWidget *scale_high;
GtkWidget *scale_start_x;
GtkWidget *scale_start_y;
GtkWidget *label_eps;
GtkWidget *label_lambda;
GtkWidget *label_low;
GtkWidget *label_high;
GtkWidget *label_start_x;
GtkWidget *label_start_y;
GtkWidget *label_formula;
GtkWidget *label_result;
//GtkWidget *image;

GtkWidget *vbox;
GtkWidget *hbox_btn;
GtkWidget *hbox_eps_lambda;
GtkWidget *hbox_low_high;
GtkWidget *hbox_start_x_y;
GtkWidget *halign_btn;
GtkWidget *halign_eps_lambda;
GtkWidget *halign_low_high;
GtkWidget *halign_start_x_y;
GtkWidget *valign;

double (*fn_x1x2)(double x1, double x2);
int ind_method = -1;
int ind_lw = -1;
int ind_var = -1;
int is_setup = 0;
int start_x;
int start_y;
int low = LOW;
int high = HIGH;
double eps;
double lambda;

void
setup_work(int ind_lw, int ind_var)
{
  gtk_label_set_text(GTK_LABEL(label_formula), strss_f_lw[ind_lw][ind_var]);
  for(int i = 10; i >= 0; i--)
    gtk_combo_box_remove_text(GTK_COMBO_BOX(combo_method), i);
  for(int i = 0; i < strss_m_lw_len[ind_lw]; i++)
    gtk_combo_box_prepend_text(GTK_COMBO_BOX(combo_method),
                               strss_m_lw[ind_lw][i]);  
}

void
combo_variant_selected(GtkWidget *widget, gpointer window)
{
  if (gtk_combo_box_get_active(GTK_COMBO_BOX(combo_lab_work)) != -1) {
    setup_work(gtk_combo_box_get_active(
               GTK_COMBO_BOX(combo_lab_work)),
                 gtk_combo_box_get_active(
               GTK_COMBO_BOX(combo_variant)));
  }
  is_setup = 0;
}

void
combo_lab_work_selected(GtkWidget *widget, gpointer window)
{
  if (gtk_combo_box_get_active(GTK_COMBO_BOX(combo_variant)) != -1) {
    setup_work(gtk_combo_box_get_active(
               GTK_COMBO_BOX(combo_lab_work)),
                 gtk_combo_box_get_active(
               GTK_COMBO_BOX(combo_variant)));
  }
  is_setup = 0;
}

void
combo_method_selected(GtkWidget *widget, gpointer window)
{
  if (gtk_combo_box_get_active(GTK_COMBO_BOX(combo_variant)) != -1
      && gtk_combo_box_get_active(GTK_COMBO_BOX(combo_variant)) != -1) {
    ind_method = gtk_combo_box_get_active(GTK_COMBO_BOX(combo_method));
    ind_lw = gtk_combo_box_get_active(GTK_COMBO_BOX(combo_lab_work));
    ind_var = gtk_combo_box_get_active(GTK_COMBO_BOX(combo_variant));
    is_setup = 1;

    /* interface setup */
    switch(ind_lw) {
      case 0: break;
      case 1: break;
      case 2: break;
      case 3: break;
      case 4: break;
      case 5: break;
      case 6: {
        switch(ind_method) {
          case 0: { /* метод наискорейшего спуска */
            gtk_widget_show(label_eps);
            gtk_widget_show(scale_eps);
            gtk_widget_hide(label_lambda);
            gtk_widget_hide(scale_lambda);
            gtk_widget_show(label_low);
            gtk_widget_show(scale_low);
            gtk_widget_show(label_high);
            gtk_widget_show(scale_high);
            gtk_widget_show(label_start_x);
            gtk_widget_show(scale_start_x);
            gtk_widget_show(label_start_y);
            gtk_widget_show(scale_start_y);
          } break;
          case 1: { /* метод циклического покоординатного спуска */
            gtk_widget_show(label_eps);
            gtk_widget_show(scale_eps);
            gtk_widget_show(label_lambda);
            gtk_widget_show(scale_lambda);
            gtk_widget_show(label_low);
            gtk_widget_show(scale_low);
            gtk_widget_show(label_high);
            gtk_widget_show(scale_high);
            gtk_widget_show(label_start_x);
            gtk_widget_show(scale_start_x);
            gtk_widget_show(label_start_y);
            gtk_widget_show(scale_start_y);
          } break;
        }
      } break;
      case 7: break;
      case 8: {
        switch(ind_method) {
          case 0: { /* Метод штрафных функций */
            gtk_widget_show(label_eps);
            gtk_widget_show(scale_eps);
            gtk_widget_show(label_lambda);
            gtk_widget_show(scale_lambda);
            gtk_widget_hide(label_low);
            gtk_widget_hide(scale_low);
            gtk_widget_hide(label_high);
            gtk_widget_hide(scale_high);
            gtk_widget_show(label_start_x);
            gtk_widget_show(scale_start_x);
            gtk_widget_show(label_start_y);
            gtk_widget_show(scale_start_y);
          } break;
        }
      } break;
    }
  }
}

void
scale_eps_changed(GtkRange *range, gpointer data)
{
  double val = gtk_range_get_value(GTK_RANGE(scale_eps));
  val = pow(val, 2);
  eps = val;
  char buf[50];
  sprintf(buf, "\u03B5: %f", val);
  gtk_label_set_text(GTK_LABEL(label_eps), buf);
}

void
scale_lambda_changed(GtkRange *range, gpointer data)
{
  double val = gtk_range_get_value(GTK_RANGE(scale_lambda));
  val = pow(val, 2);
  lambda = val;
  char buf[50];
  sprintf(buf, "\u03BB: %f", val);
  gtk_label_set_text(GTK_LABEL(label_lambda), buf);
}

void
scale_low_changed(GtkRange *range, gpointer data)
{
  double val = gtk_range_get_value(GTK_RANGE(scale_low));
  low = val;
  char buf[50];
  sprintf(buf, "от: %.2f", val);
  gtk_label_set_text(GTK_LABEL(label_low), buf);
}

void
scale_high_changed(GtkRange *range, gpointer data)
{
  double val = gtk_range_get_value(GTK_RANGE(scale_high));
  high = val;
  char buf[50];
  sprintf(buf, "до: %.2f", val);
  gtk_label_set_text(GTK_LABEL(label_high), buf);
}

void
scale_start_x_changed(GtkRange *range, gpointer data)
{
  double val = gtk_range_get_value(GTK_RANGE(scale_start_x));
  start_x = val;
  char buf[50];
  sprintf(buf, "x1: %.2f", val);
  gtk_label_set_text(GTK_LABEL(label_start_x), buf);
}

void
scale_start_y_changed(GtkRange *range, gpointer data)
{
  double val = gtk_range_get_value(GTK_RANGE(scale_start_y));
  start_y = val;
  char buf[50];
  sprintf(buf, "x2: %.2f", val);
  gtk_label_set_text(GTK_LABEL(label_start_y), buf);
}

void
calc_btn_clicked(GtkWidget *widget, gpointer data)
{
  if(is_setup) {
    switch(ind_lw) {
      case 0: break;
      case 1: break;
      case 2: break;
      case 3: break;
      case 4: break;
      case 5: break;
      case 6: {
        switch(ind_method) {
          case 0: { /* метод наискорейшего спуска */
            fn_x1x2 = make_func_x1x2_from_expr(strs_f_lw7[ind_var]);
            struct xy xy1 = find_xy_min_cycle_descent(fn_x1x2,
                                                      start_x, start_y,
                                                      low, high, eps);
            char output[100];
            sprintf(output, "f(x)=%f, x1=%f, x2=%f",
              fn_x1x2(xy1.x, xy1.y), xy1.x, xy1.y);
            gtk_label_set_text(GTK_LABEL(label_result), output);
          } break;
          case 1: { /* метод циклического покоординатного спуска */
            fn_x1x2 = make_func_x1x2_from_expr(strs_f_lw7[ind_var]);
            struct xy xy1 = find_xy_min_quickest_descent(fn_x1x2,
                                                         start_x, start_y,
                                                         low, high, eps,
                                                         lambda);
            char output[100];
            sprintf(output, "f(x)=%f, x1=%f, x2=%f",
              fn_x1x2(xy1.x, xy1.y), xy1.x, xy1.y);
            gtk_label_set_text(GTK_LABEL(label_result), output);
          } break;
        }
      } break;
      case 7: break;
      case 8: {
        switch(ind_method) {
          case 0: { /* Метод штрафных функций */
            struct xy xy1 = penalty_functions_method_max(
                       fs_lw9[ind_var], g1s_lw9[ind_var], g2s_lw9[ind_var],
                       *b1s_lw9[ind_var], *b2s_lw9[ind_var],
                       start_x, start_y, eps, lambda);
            char output[100];
            sprintf(output, "f(x)=%f, x1=%f, x2=%f",
              fs_lw9[ind_var](xy1.x, xy1.y), xy1.x, xy1.y);
            gtk_label_set_text(GTK_LABEL(label_result), output);
          } break;
        }
      } break;
    }
  } else {
    GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window),
                                 GTK_DIALOG_DESTROY_WITH_PARENT,
                                 GTK_MESSAGE_ERROR,
                                 GTK_BUTTONS_CLOSE,
                                 "Установите вариант, номер работы и метод");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
  }
}

int
main(int argc, char *argv[])
{
  gtk_init(&argc, &argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(window), 500, 500);
  gtk_window_set_title(GTK_WINDOW(window),
    "Математическое программирование");
  gtk_container_set_border_width(GTK_CONTAINER(window), 10);

  calc_btn = gtk_button_new_with_label("Считать");
  exit_btn = gtk_button_new_with_label("Выход");
  
  label_formula = gtk_label_new("Установите вариант, номер работы и метод");
  label_result = gtk_label_new("Здесь будут отображены результаты");

  combo_variant = gtk_combo_box_new_text();
  {
    char buf[3];
    for(int i = 1; i <= COUNT_VARIANT; i++) {
      gtk_combo_box_append_text(GTK_COMBO_BOX(combo_variant),
        concat("Вариант ", itoa(i, buf, 10)));
    }
  }

  combo_lab_work = gtk_combo_box_new_text();
  {
    char buf[2];
    for(int i = 1; i <= COUNT_LW; i++) {
      gtk_combo_box_append_text(GTK_COMBO_BOX(combo_lab_work),
        concat("Лабораторная №", itoa(i, buf, 10)));
    }
  }

  combo_method = gtk_combo_box_new_text();

  label_eps = gtk_label_new("\u03B5");
  label_lambda = gtk_label_new("\u03BB");
  label_low = gtk_label_new("от");
  label_high = gtk_label_new("до");
  label_start_x = gtk_label_new("x1");
  label_start_y = gtk_label_new("x2");

  scale_eps = gtk_hscale_new_with_range(0.001, 1, 0.04995);
  gtk_scale_set_draw_value(GTK_SCALE(scale_eps), FALSE);
  gtk_range_set_value(GTK_RANGE(scale_eps), sqrt(0.01));
  gtk_scale_set_digits(GTK_SCALE(scale_eps), 20);
  
  scale_lambda = gtk_hscale_new_with_range(0.01, 1, 0.0495);
  gtk_scale_set_draw_value(GTK_SCALE(scale_lambda), FALSE);
  gtk_range_set_value(GTK_RANGE(scale_lambda), sqrt(0.1));
  gtk_scale_set_digits(GTK_SCALE(scale_lambda), 20);

  scale_low = gtk_hscale_new_with_range(-10, 10, 0.1);
  gtk_scale_set_draw_value(GTK_SCALE(scale_low), FALSE);
  gtk_range_set_value(GTK_RANGE(scale_low), low);
  
  scale_high = gtk_hscale_new_with_range(-10, 10, 0.1);
  gtk_scale_set_draw_value(GTK_SCALE(scale_high), FALSE);
  gtk_range_set_value(GTK_RANGE(scale_high), high);
  
  scale_start_x = gtk_hscale_new_with_range(-10, 10, 0.1);
  gtk_scale_set_draw_value(GTK_SCALE(scale_start_x), FALSE);
  gtk_range_set_value(GTK_RANGE(scale_start_x), start_x);
  
  scale_start_y = gtk_hscale_new_with_range(-10, 10, 0.1);
  gtk_scale_set_draw_value(GTK_SCALE(scale_start_y), FALSE);
  gtk_range_set_value(GTK_RANGE(scale_start_y), start_y);

  //image = gtk_image_new_from_file("ezha_small.png");

  vbox = gtk_vbox_new(FALSE, 5);
  hbox_btn = gtk_hbox_new(TRUE, 3);
  hbox_eps_lambda = gtk_hbox_new(TRUE, 3);
  hbox_low_high = gtk_hbox_new(TRUE, 3);
  hbox_start_x_y = gtk_hbox_new(TRUE, 3);
  
  valign = gtk_alignment_new(0, 1, 0, 0);
  halign_btn = gtk_alignment_new(1, 0, 1, 0);
  halign_eps_lambda = gtk_alignment_new(1, 0, 1, 0);
  halign_low_high = gtk_alignment_new(1, 0, 1, 0);
  halign_start_x_y = gtk_alignment_new(1, 0, 1, 0);
  
  gtk_container_add(GTK_CONTAINER(vbox), valign);
  gtk_container_add(GTK_CONTAINER(window), vbox);
  gtk_container_add(GTK_CONTAINER(hbox_btn), calc_btn);
  gtk_container_add(GTK_CONTAINER(hbox_btn), exit_btn);
  gtk_container_add(GTK_CONTAINER(hbox_eps_lambda), label_eps);
  gtk_container_add(GTK_CONTAINER(hbox_eps_lambda), scale_eps);
  gtk_container_add(GTK_CONTAINER(hbox_eps_lambda), label_lambda);
  gtk_container_add(GTK_CONTAINER(hbox_eps_lambda), scale_lambda);
  gtk_container_add(GTK_CONTAINER(hbox_low_high), label_low);
  gtk_container_add(GTK_CONTAINER(hbox_low_high), scale_low);
  gtk_container_add(GTK_CONTAINER(hbox_low_high), label_high);
  gtk_container_add(GTK_CONTAINER(hbox_low_high), scale_high);
  gtk_container_add(GTK_CONTAINER(hbox_start_x_y), label_start_x);
  gtk_container_add(GTK_CONTAINER(hbox_start_x_y), scale_start_x);
  gtk_container_add(GTK_CONTAINER(hbox_start_x_y), label_start_y);
  gtk_container_add(GTK_CONTAINER(hbox_start_x_y), scale_start_y);
  gtk_container_add(GTK_CONTAINER(halign_btn), hbox_btn);
  gtk_container_add(GTK_CONTAINER(halign_eps_lambda), hbox_eps_lambda);
  gtk_container_add(GTK_CONTAINER(halign_low_high), hbox_low_high);
  gtk_container_add(GTK_CONTAINER(halign_start_x_y), hbox_start_x_y);

  //gtk_box_pack_start(GTK_BOX(vbox), image, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(vbox), label_result, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(vbox), label_formula, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(vbox), halign_start_x_y, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(vbox), halign_low_high, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(vbox), halign_eps_lambda, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(vbox), combo_method, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(vbox), combo_lab_work, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(vbox), combo_variant, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(vbox), halign_btn, FALSE, FALSE, 0);

  g_signal_connect(G_OBJECT(exit_btn), "clicked", 
    G_CALLBACK(gtk_main_quit), G_OBJECT(window));
  
  g_signal_connect(G_OBJECT(calc_btn), "clicked", 
    G_CALLBACK(calc_btn_clicked), NULL);
  
  g_signal_connect(G_OBJECT(combo_variant), "changed", 
    G_CALLBACK(combo_variant_selected), (gpointer) label_formula);
  
  g_signal_connect(G_OBJECT(combo_method), "changed", 
    G_CALLBACK(combo_method_selected), (gpointer) label_formula);
  
  g_signal_connect(G_OBJECT(combo_lab_work), "changed", 
    G_CALLBACK(combo_lab_work_selected), (gpointer) label_formula);

  g_signal_connect(G_OBJECT(scale_eps), "value-changed", 
    G_CALLBACK(scale_eps_changed), NULL);
  
  g_signal_connect(G_OBJECT(scale_lambda), "value-changed", 
    G_CALLBACK(scale_lambda_changed), NULL);
   
  g_signal_connect(G_OBJECT(scale_low), "value-changed", 
    G_CALLBACK(scale_low_changed), NULL);
  
  g_signal_connect(G_OBJECT(scale_high), "value-changed", 
    G_CALLBACK(scale_high_changed), NULL);
  
  g_signal_connect(G_OBJECT(scale_start_x), "value-changed", 
    G_CALLBACK(scale_start_x_changed), NULL);
  
  g_signal_connect(G_OBJECT(scale_start_y), "value-changed", 
    G_CALLBACK(scale_start_y_changed), NULL);
  
  g_signal_connect(G_OBJECT(window), "destroy",
    G_CALLBACK(gtk_main_quit), G_OBJECT(window));

  gtk_widget_show_all(window);
  
  gtk_widget_hide(label_eps);
  gtk_widget_hide(scale_eps);
  gtk_widget_hide(label_lambda);
  gtk_widget_hide(scale_lambda);
  gtk_widget_hide(label_low);
  gtk_widget_hide(scale_low);
  gtk_widget_hide(label_high);
  gtk_widget_hide(scale_high);
  gtk_widget_hide(label_start_x);
  gtk_widget_hide(scale_start_x);
  gtk_widget_hide(label_start_y);
  gtk_widget_hide(scale_start_y);

  scale_eps_changed(GTK_RANGE(scale_eps), NULL);
  scale_lambda_changed(GTK_RANGE(scale_lambda), NULL);
  scale_low_changed(GTK_RANGE(scale_low), NULL);
  scale_high_changed(GTK_RANGE(scale_high), NULL);
  scale_start_x_changed(GTK_RANGE(scale_start_x), NULL);
  scale_start_y_changed(GTK_RANGE(scale_start_y), NULL);

  gtk_main();
}

#endif
