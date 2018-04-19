#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <string.h>

static void activate(GtkApplication* app,gpointer data);
static void open_file(GtkWidget* widget,gpointer data);
static void translate(gchar* filename);
static void show_translate(GtkWidget* widget,gpointer data);

GString* translation;

int main(int argc,char** argv)
{
    GtkApplication* app;
    int status;

    translation=g_string_new(NULL);

    app=gtk_application_new("org.hzl.example",G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app,"activate",G_CALLBACK(activate),NULL);
    status=g_application_run(G_APPLICATION(app),argc,argv);

    g_object_unref(app);
    return status;
}

static void activate(GtkApplication* app,gpointer data)
{
    GtkWidget *window,*scrolled_window,*text_view;
    GtkWidget *vbox,*hbox,*hbox2,*button,*button2;
    GtkTextBuffer *buffer;

    GtkWidget *scrolled_window2,*text_view2;
    GtkTextBuffer *buffer2;

    window=gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window),"Assembler");
    gtk_window_set_default_size(GTK_WINDOW(window),800,600);

    buffer=gtk_text_buffer_new(NULL);
    text_view=gtk_text_view_new_with_buffer(buffer);
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(text_view),GTK_WRAP_WORD);

    buffer2=gtk_text_buffer_new(NULL);
    text_view2=gtk_text_view_new_with_buffer(buffer2);
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(text_view2),GTK_WRAP_WORD);

    vbox=gtk_box_new(GTK_ORIENTATION_VERTICAL,5);
    hbox=gtk_box_new(GTK_ORIENTATION_HORIZONTAL,5);
    hbox2=gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);

    button=gtk_button_new_with_mnemonic("_Open File");
    button2=gtk_button_new_with_mnemonic("_Translate");

    scrolled_window=gtk_scrolled_window_new(NULL,NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window),GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);
    gtk_container_add(GTK_CONTAINER(scrolled_window),text_view);
    gtk_container_set_border_width(GTK_CONTAINER(scrolled_window),5);

    scrolled_window2=gtk_scrolled_window_new(NULL,NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window2),GTK_POLICY_AUTOMATIC,GTK_POLICY_AUTOMATIC);
    gtk_container_add(GTK_CONTAINER(scrolled_window2),text_view2);
    gtk_container_set_border_width(GTK_CONTAINER(scrolled_window2),5);

    gtk_box_pack_start(GTK_BOX(vbox),hbox,TRUE,TRUE,0);
    gtk_box_pack_start(GTK_BOX(vbox),hbox2,FALSE,FALSE,0);

    gtk_container_add(GTK_CONTAINER(window),vbox);

    gtk_box_pack_start(GTK_BOX(hbox),scrolled_window,TRUE,TRUE,0);
    gtk_box_pack_start(GTK_BOX(hbox),scrolled_window2,TRUE,TRUE,0);

    gtk_box_pack_start(GTK_BOX(hbox2),button,TRUE,TRUE,0);
    gtk_box_pack_start(GTK_BOX(hbox2),button2,TRUE,TRUE,0);

    g_signal_connect(button,"clicked",G_CALLBACK(open_file),buffer);
    g_signal_connect(button2,"clicked",G_CALLBACK(show_translate),buffer2);

    gtk_widget_show_all(window);
}


static void open_file(GtkWidget* widget,gpointer data)
{
    GtkTextBuffer* buffer=GTK_TEXT_BUFFER(data);
    GtkWidget* parent_window=gtk_widget_get_toplevel(widget);
    GtkFileFilter* filter=gtk_file_filter_new();
    GtkWidget* dialog=gtk_file_chooser_dialog_new("Open File",GTK_WINDOW(parent_window),GTK_FILE_CHOOSER_ACTION_OPEN,"Open",GTK_RESPONSE_ACCEPT,"Cancel",GTK_RESPONSE_CANCEL,NULL);

    gtk_file_filter_add_pattern(filter,"*.asm");
    gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(dialog),filter);
    gchar* filename = NULL;
    switch(gtk_dialog_run(GTK_DIALOG(dialog)))
    {
        case GTK_RESPONSE_ACCEPT:
            {
                filename=gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
                FILE* fp;
                fp=fopen(filename,"r");
                GString* string;
                string=g_string_new(NULL);
                char text[1000];
                while(fgets(text,sizeof(text),fp)>0)
                {
                    g_string_append(string,text);
                    /*g_string_append(string,"\n");*/
                }
                fclose(fp);
                gtk_text_buffer_set_text(buffer,string->str,-1);
                g_string_free(string,TRUE);
                break;
            }
        default:
            break;
    }
    gtk_widget_destroy(dialog);
    g_string_assign(translation,"");
    translate(filename);
}

static void translate(gchar* filename)
{
    FILE* fp;
    GString* command;
    GString* tmp;
    tmp=g_string_new(NULL);
    g_string_append(tmp,"cp ");
    g_string_append(tmp,filename);
    g_string_append(tmp," /tmp/tmp.asm");
    system(tmp->str);
    command=g_string_new(NULL);
    g_string_append(command,"~/assembler.wls  /tmp/tmp.asm");

    fp=popen(command->str,"r");
    char text[1000];
    while(fgets(text,sizeof(text),fp)>0)
    {
        g_string_append(translation,text);
    }
    pclose(fp);
}

static void show_translate(GtkWidget* widget,gpointer data)
{
    GtkTextBuffer* buffer=GTK_TEXT_BUFFER(data);
    gtk_text_buffer_set_text(buffer,translation->str,-1);
}
