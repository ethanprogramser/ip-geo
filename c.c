#include<curl/curl.h>
#include<stdio.h>
#include<gtk/gtk.h>
#include<cjson/cJSON.h>
#include<string.h>

GtkWidget *lab;
GtkWidget *window;
GtkWidget *isend;
GtkWidget *ip_ent;
GtkWidget *box;

void add_all_data() {
  // open up json file and get data and put in labels
 
  GtkWidget *ip_lab;
  GtkWidget *address_lab;
  GtkWidget *postal_lab;
  GtkWidget *region_lab;
  GtkWidget *time_lab;
  GtkWidget *new_ip;

  FILE *fp = fopen("f.json", "r");
  char buffer[1024];
  int len = fread(buffer, 1, sizeof(buffer), fp);
  fclose(fp);

  cJSON *json = cJSON_Parse(buffer);
  cJSON *adre = cJSON_GetObjectItemCaseSensitive(json, "ip");
  cJSON *ip = cJSON_GetObjectItemCaseSensitive(json, "country");
  cJSON *address = cJSON_GetObjectItemCaseSensitive(json, "loc");
  cJSON *postal = cJSON_GetObjectItemCaseSensitive(json, "city");
  cJSON *region = cJSON_GetObjectItemCaseSensitive(json, "region");
  cJSON *timezone = cJSON_GetObjectItemCaseSensitive(json, "timezone");
  
  ip_lab = gtk_label_new(adre->valuestring);
  address_lab = gtk_label_new(ip->valuestring);
  postal_lab = gtk_label_new(address->valuestring);
  region_lab = gtk_label_new(region->valuestring);
  time_lab = gtk_label_new(timezone->valuestring);
  new_ip = gtk_label_new(postal->valuestring);


  gtk_container_add(GTK_CONTAINER(box), ip_lab);
  gtk_container_add(GTK_CONTAINER(box), address_lab);
  gtk_container_add(GTK_CONTAINER(box), postal_lab);
  gtk_container_add(GTK_CONTAINER(box), region_lab);
  gtk_container_add(GTK_CONTAINER(box), time_lab);
  gtk_container_add(GTK_CONTAINER(box), new_ip);

  gtk_widget_show_all(window);
}

static void request(GtkWidget *button, gpointer *pointer) {
  // get data and store in json
  char buff[55] = { 0 };
  const gchar *p = gtk_entry_get_text(GTK_ENTRY(ip_ent));
  strcat(buff, "curl https://ipinfo.io/");
  strcat(buff, p);
  strcat(buff, "> f.json");
  char *awe = strtok(buff, "");

  system(awe);
  
  add_all_data();
}

int main(int argc, char *argv[]) 
{
  gtk_init(&argc, &argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  isend = gtk_button_new_with_label("send");
  ip_ent = gtk_entry_new();
  box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  lab = gtk_label_new("Paste IP Below");

  g_signal_connect(isend, "clicked", G_CALLBACK(request), NULL);

  gtk_container_add(GTK_CONTAINER(window), box);
  gtk_container_add(GTK_CONTAINER(box), lab);
  gtk_container_add(GTK_CONTAINER(box), ip_ent);
  gtk_container_add(GTK_CONTAINER(box), isend);

  GtkCssProvider *provider = gtk_css_provider_new();
  gtk_css_provider_load_from_path(provider, "theme.css", NULL);
  gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
                                      GTK_STYLE_PROVIDER(provider),
                                      GTK_STYLE_PROVIDER_PRIORITY_USER);
  
  gtk_widget_show_all(window);
  gtk_main();
  return 0;
}
