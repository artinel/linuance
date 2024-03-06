GtkBuilder* load_ui(char *ui){
	GtkBuilder *builder = gtk_builder_new();
	gtk_builder_add_from_file(GTK_BUILDER(builder), ui, NULL);
	return builder;
}

void load_css(GtkWidget *widget, char *css){
	GtkCssProvider *provider = gtk_css_provider_new();
	gtk_css_provider_load_from_path(provider, css);
	gtk_style_context_add_provider_for_display(gtk_widget_get_display(widget), 
			GTK_STYLE_PROVIDER(provider),
			GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
}
