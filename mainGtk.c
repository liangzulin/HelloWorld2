#include <gtk/gtk.h>

//Start Data Definition
typedef struct
{
  const gboolean  fixed;
  const guint     number;
  const gchar    *severity;
  const gchar    *description;
}Bug;
enum{
  COLUMN_FIXED,
  COLUMN_NUMBER,
  COLUMN_SEVERITY,
  COLUMN_DESCRIPTION,
  COLUMN_PULSE,
  COLUMN_ICON,
  COLUMN_ACTIVE,
  COLUMN_SENSITIVE,
  NUM_COLUMNS
};
static Bug data[] ={
  { FALSE, 60482, "Normal",     "scrollable notebooks and hidden tabs" },
  { FALSE, 60620, "Critical",   "gdk_window_clear_area (gdkwindow-win32.c) is not thread-safe" },
  { FALSE, 50214, "Major",      "Xft support does not clean up correctly" },
  { TRUE,  52877, "Major",      "GtkFileSelection needs a refresh method. " },
  { FALSE, 56070, "Normal",     "Can't click button after setting in sensitive" },
  { TRUE,  56355, "Normal",     "GtkLabel - Not all changes propagate correctly" },
  { FALSE, 50055, "Normal",     "Rework width/height computations for TreeView" },
  { FALSE, 58278, "Normal",     "gtk_dialog_set_response_sensitive () doesn't work" },
  { FALSE, 55767, "Normal",     "Getters for all setters" },
  { FALSE, 56925, "Normal",     "Gtkcalender size" },
  { FALSE, 56221, "Normal",     "Selectable label needs right-click copy menu" },
  { TRUE,  50939, "Normal",     "Add shift clicking to GtkTextView" },
  { FALSE, 6112,  "Enhancement","netscape-like collapsable toolbars" },
  { FALSE, 1,     "Normal",     "First bug :=)" },
};
//End Data Definition
static void fixed_toggled (GtkCellRendererToggle *cell,
               							   gchar *path_str,
               							gpointer  data){
  GtkTreeModel *model = (GtkTreeModel*) data;
  GtkTreeIter  iter;
  GtkTreePath *path = gtk_tree_path_new_from_string (path_str);
  gboolean fixed;

  /* get toggled iter */
  gtk_tree_model_get_iter (model, &iter, path);
  gtk_tree_model_get (model, &iter, COLUMN_FIXED, &fixed, -1);

  /* do something with the value */
  fixed ^= 1;

  /* set new value */
  gtk_list_store_set (GTK_LIST_STORE (model), &iter, COLUMN_FIXED, fixed, -1);

  /* clean up */
  gtk_tree_path_free (path);
}


GObject *treeview;

void initTreeView(){
	GtkTreeModel *model;
		
	//Create Data
	gint i = 0;
	GtkListStore *store;
	GtkTreeIter iter;

  /* create list store */
  store = gtk_list_store_new (NUM_COLUMNS,
                              G_TYPE_BOOLEAN,
                              G_TYPE_UINT,
                              G_TYPE_STRING,
                              G_TYPE_STRING,
                              G_TYPE_UINT,
                              G_TYPE_STRING,
                              G_TYPE_BOOLEAN,
                              G_TYPE_BOOLEAN);
	
	/* add data to the list store */
	for (i = 0; i < G_N_ELEMENTS (data); i++){
		gchar *icon_name;
      	gboolean sensitive;

      if (i == 1 || i == 3)
        icon_name = "battery-caution-charging-symbolic";
      else
        icon_name = NULL;
      if (i == 3)
        sensitive = FALSE;
      else
        sensitive = TRUE;
      gtk_list_store_append (store, &iter);
      gtk_list_store_set (store, &iter,
                          COLUMN_FIXED, data[i].fixed,
                          COLUMN_NUMBER, data[i].number,
                          COLUMN_SEVERITY, data[i].severity,
                          COLUMN_DESCRIPTION, data[i].description,
                          COLUMN_PULSE, 0,
                          COLUMN_ICON, icon_name,
                          COLUMN_ACTIVE, FALSE,
                          COLUMN_SENSITIVE, sensitive,
                          -1);
    }
	
	model=GTK_TREE_MODEL(store);
	//model=gtk_tree_view_get_model((GtkTreeView*)treeview);
	gtk_tree_view_set_model((GtkTreeView*)treeview, model);
	
	
	GtkCellRenderer* renderer;
	GtkTreeViewColumn *column;
	
	renderer=gtk_cell_renderer_toggle_new ();
	g_signal_connect (renderer, "toggled",G_CALLBACK (fixed_toggled), model);	
	column = gtk_tree_view_column_new_with_attributes ("Fixed?",renderer,"active", COLUMN_FIXED,NULL);
	
	/* set this column to a fixed sizing (of 50 pixels) */
	gtk_tree_view_column_set_sizing (GTK_TREE_VIEW_COLUMN (column),GTK_TREE_VIEW_COLUMN_FIXED);
	gtk_tree_view_column_set_fixed_width (GTK_TREE_VIEW_COLUMN (column), 50);
	gtk_tree_view_append_column ((GtkTreeView*)treeview, column);
	/* column for bug numbers */
	renderer = gtk_cell_renderer_text_new ();
	column = gtk_tree_view_column_new_with_attributes ("Bug number",renderer,"text",COLUMN_NUMBER,NULL);
	gtk_tree_view_column_set_sort_column_id (column, COLUMN_NUMBER);
	gtk_tree_view_append_column ((GtkTreeView*)treeview, column);
	
	renderer = gtk_cell_renderer_text_new ();
	column = gtk_tree_view_column_new_with_attributes ("COLUMN_DESCRIPTION",renderer,"text",COLUMN_DESCRIPTION,NULL);
	gtk_tree_view_column_set_sort_column_id (column, COLUMN_DESCRIPTION);
	gtk_tree_view_append_column ((GtkTreeView*)treeview, column);
	
	
	//GtkTreeIter iter;
	gboolean valid;
	gint row_count = 0;
	valid = gtk_tree_model_get_iter_first (model,&iter);
	gtk_list_store_set (store, &iter,
                          COLUMN_FIXED, data[i].fixed,
                          COLUMN_NUMBER, 20,
                          COLUMN_SEVERITY, data[i].severity,
                          COLUMN_DESCRIPTION, "sgdfrgs",
                          COLUMN_PULSE, 0,
                          COLUMN_ICON, "battery-caution-charging-symbolic",
                          COLUMN_ACTIVE, FALSE,
                          COLUMN_SENSITIVE, TRUE,
                          -1);
}
void on_window_destroy (GtkWidget *object, gpointer user_data) {
    gtk_main_quit();
}
static void print_hello (GtkWidget *widget, gpointer data){
	g_print ("Hello World\n");
	
	GtkTreeModel *model;
	//Create Data
	gint i = 0;
	GtkListStore *store;
	GtkTreeIter iter;
	
	gchar *str_data;
	gint   int_data;
	// Make sure you terminate calls to gtk_tree_model_get() with a ¡°-1¡± value
	
	model=gtk_tree_view_get_model((GtkTreeView*)treeview);
	g_print("\n\nStep1     model=gtk_tree_view_get_model(this->treeview);\n");
	
	gboolean error = gtk_tree_model_get_iter_first (model,&iter);
	gchar *str_data2;
	gint   int_data2;
		
		// Make sure you terminate calls to gtk_tree_model_get() with a ¡°-1¡± value
	gtk_tree_model_get (model, &iter,
                       COLUMN_DESCRIPTION, &str_data2,
                       COLUMN_NUMBER, &int_data2,
                       -1);
	g_print("Step2     gtk_tree_model_get_iter_first (model,&iter);\n",error);
	
	/* create list store */
	store = gtk_list_store_new (NUM_COLUMNS,
                              G_TYPE_BOOLEAN,
                              G_TYPE_UINT,
                              G_TYPE_STRING,
                              G_TYPE_STRING,
                              G_TYPE_UINT,
                              G_TYPE_STRING,
                              G_TYPE_BOOLEAN,
                              G_TYPE_BOOLEAN);
	//gdk_threads_enter(); 
	gtk_list_store_set (store, &iter,
                          COLUMN_FIXED, TRUE,
                          COLUMN_NUMBER, int_data2 + 3,
                          COLUMN_SEVERITY, FALSE,
                          COLUMN_DESCRIPTION, "ABCABC bbc bbc",
                          COLUMN_PULSE, 0,
                          COLUMN_ICON, "battery-caution-charging-symbolic",
                          COLUMN_ACTIVE, FALSE,
                          COLUMN_SENSITIVE, TRUE,
                          -1);
    //gdk_threads_leave();
	
    // Before it is success!
                          
	int row_count=0;
	gboolean valid=TRUE;
	while (valid){
		gchar *str_data;
		gint   int_data;
		
		// Make sure you terminate calls to gtk_tree_model_get() with a ¡°-1¡± value
		gtk_tree_model_get (model, &iter,
                       COLUMN_DESCRIPTION, &str_data,
                       COLUMN_NUMBER, &int_data,
                       -1);
		// Do something with the data
		g_print ("Row %d: (%s,%d)\n",row_count, str_data, int_data);
		g_free (str_data);
		valid = gtk_tree_model_iter_next (model,&iter);
		
		row_count++;
	}
	
}


int main(int argc, char** argv) {
	GtkWidget *window;
	GObject *button;
	GtkBuilder *builder;
	
	gtk_init (&argc, &argv);

    builder = gtk_builder_new ();
    gtk_builder_add_from_file (builder, "a4.glade", NULL);
    
    window = GTK_WIDGET (gtk_builder_get_object (builder, "window1"));
    button = gtk_builder_get_object (builder, "button1");
	treeview = gtk_builder_get_object (builder, "treeview3");
	
	initTreeView();
	
	g_signal_connect (window, "destroy", G_CALLBACK (on_window_destroy), NULL);
	g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);

	gtk_widget_show (window);
	gtk_main (); 
    
	return 0;
}
