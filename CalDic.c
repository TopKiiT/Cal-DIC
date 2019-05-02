#include <gtk/gtk.h>
#include <string.h>
#include <glib/gi18n.h>
#include <stdlib.h>
#include <stdio.h>
#include <gdk-pixbuf/gdk-pixbuf.h>
#include <stdbool.h> 
static float percent = 0.0;
static float bmi;
static GtkWidget *window = NULL;
static int total_cal = 0;
static GtkWidget *window2,*window3;
static GtkWidget *assistant,*bmiimage;
static guint j;
static char buffer1[32],buffer2[32],buffer3[32],buffer4[32],gender[32],overcal[32];
char text[20000];
static GtkWidget *text1;
static GtkWidget *text2;
static GtkWidget *text3;
static void meal_check   (GtkEditable*, GtkAssistant*);
static void assistant_cancel (GtkAssistant*, gpointer);
static void assistant_close  (GtkAssistant*, gpointer);
static void button_clicked( GtkWidget*, gchar*);
char *name = "empty";
static GtkWidget *label5,*label6,*label7,*label8,*label9,*label10,*label11,*label12,*label13,*label14,*label15,*label16,*label17;
int gender_check;
int num1;
typedef struct {
    GtkWidget *widget;
    char food[2000];
    char cal[100];
} Info;

typedef struct {
  GtkWidget *widget;
  gint index;
  const gchar *title;
  GtkAssistantPageType type;
  gboolean complete;
} PageInfo;

static Info rec[800];
static Info test[800];
static int i = 0;
static char check[20];
static int break_cal;
static int luach_cal;
static int din_cal;
static bool break_check;
static bool luach_check;
static bool din_check;
static PageInfo page[5] = {
    { NULL, -1, "BMI",           GTK_ASSISTANT_PAGE_INTRO,    TRUE},
    { NULL, -1, "Calorie",       GTK_ASSISTANT_PAGE_CONTENT,  FALSE},
    { NULL, -1, "Total",       GTK_ASSISTANT_PAGE_CONTENT,  TRUE},
    { NULL, -1, "Summary ",       GTK_ASSISTANT_PAGE_SUMMARY,  TRUE},
  };


void csv_read(){
    FILE *f = fopen("CSV.csv", "r");
    char str[800] = "";
    char *token;
    char *delim = ",";
     while (fgets(str, sizeof(str), f) != NULL) {
   
        token = strtok(str, delim);
        int col = 0;
        while (token != NULL) {
            switch (col) {
                case 0:
                    strcpy(rec[i].food, token);
                    break;
                case 1:
                strcpy(rec[i].cal, token);
          
                    break;
            }
            col++;
            token = strtok(NULL, delim);
        }       
 
        i++;        
    }
    fclose(f);
}

static void button_clicked( GtkWidget *widget, gchar *data){
   
    int cal = atoi((char *) data);
    
    if(strcmp(check, "Breakfast") == 0){
    	break_check = TRUE;
    	break_cal = cal;
    	}
    else if(strcmp(check, "Lunch") == 0){
        luach_check = TRUE;
        luach_cal = cal;
        }
    else if(strcmp(check, "Dinner") == 0){
        din_check = TRUE;
        din_cal = cal;
        }
    
        total_cal=break_cal+luach_cal+din_cal;
        
        snprintf(buffer1, sizeof(buffer1), "%d Kcal", break_cal);
        
        snprintf(buffer2, sizeof(buffer2), "%d Kcal", luach_cal);
        
        snprintf(buffer3, sizeof(buffer3), "%d Kcal", din_cal);
        
        snprintf(buffer4, sizeof(buffer4), "%d Kcal", total_cal);
        gtk_label_set_text(GTK_LABEL(label8),buffer1);
        gtk_label_set_text(GTK_LABEL(label9),buffer2);
        gtk_label_set_text(GTK_LABEL(label10),buffer3);
        gtk_label_set_text(GTK_LABEL(label12),buffer4);


         
         if (gender_check == 1)
         {
         	snprintf(gender, sizeof(gender), "%d Kcal", num1*31);
         	snprintf(overcal, sizeof(overcal), "%d Kcal", total_cal - num1*31);
         }
         else if (gender_check == 2)
         {
         	snprintf(gender, sizeof(gender), "%d Kcal", num1*27);
         	snprintf(overcal, sizeof(overcal), "%d Kcal", total_cal - num1*27);
         }
         gtk_label_set_text(GTK_LABEL(label14),buffer4);
        gtk_label_set_text(GTK_LABEL(label15),gender);
        gtk_label_set_text(GTK_LABEL(label16),overcal);
    
    
    
    //g_print("%d \n", total_cal);
    gtk_window_close (GTK_WINDOW(window2));

    return;
}

static void close_window(GtkWindow *window, gpointer data)
{
    gtk_window_close (GTK_WINDOW(window2)); 
}
static void close_ad(GtkWindow *window, gpointer data)
{
    gtk_window_close (GTK_WINDOW(window3)); 
}

int choosefood(GtkWidget *widget,gchar *data) {
    
    GtkWidget *myButton, *label, *myGrid, *scrolled, *meal, *foodname, *cal;
    
    strcpy (check,(char *) data);
    if(strcmp(check, "Breakfast") == 0){
    	GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file_at_scale("Breakfast.png",200,75,1, NULL );
		meal = gtk_image_new_from_pixbuf(pixbuf);
    	}
    else if(strcmp(check, "Lunch") == 0){
        GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file_at_scale("Lunch.png",200,75,1, NULL );
		meal = gtk_image_new_from_pixbuf(pixbuf);
        }
    else if(strcmp(check, "Dinner") == 0){
         GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file_at_scale("Dinner.png",200,75,1, NULL );
		meal = gtk_image_new_from_pixbuf(pixbuf);
        }

    window2 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_name(window2,"window2");
    gtk_window_set_default_size(GTK_WINDOW(window2), 500, 500);
    myGrid = gtk_grid_new();
    gtk_widget_set_name(myGrid,"myGrid");
    
    foodname = gtk_label_new("ชื่ออาหาร");
    cal = gtk_label_new("จำนวนแคลลอรี่(กิโลแคลลอรี่)");
    gtk_grid_attach(GTK_GRID(myGrid), meal, 1, 0, 2, 1);
    gtk_grid_attach(GTK_GRID(myGrid), foodname, 1, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(myGrid), cal, 2, 1, 1, 1);
    gtk_widget_set_margin_bottom(meal,20);
    
    for (j = 0; j < i; ++j)
    {
        

         rec[j].widget = gtk_button_new_with_label(rec[j].food);
         test[j].widget = gtk_button_new_with_label(rec[j].cal);
        gtk_grid_attach(GTK_GRID(myGrid), rec[j].widget, 1, j+2, 1, 1);
        gtk_grid_attach(GTK_GRID(myGrid), test[j].widget, 2, j+2, 1, 1);
        g_signal_connect (rec[j].widget,
                  "clicked", G_CALLBACK(button_clicked),rec[j].cal);
        g_signal_connect (rec[j].widget, "clicked",
                    G_CALLBACK (meal_check), (gpointer) assistant);
        
        g_signal_connect (test[j].widget,
                  "clicked", G_CALLBACK(button_clicked),rec[j].cal);
        g_signal_connect (test[j].widget, "clicked",
                    G_CALLBACK (meal_check), (gpointer) assistant);
        
    }

    gtk_widget_set_halign(myGrid,GTK_ALIGN_CENTER);
    gtk_widget_set_valign(myGrid,GTK_ALIGN_CENTER);

    g_signal_connect (window2, "destroy", 
        G_CALLBACK(close_window), NULL);


    scrolled = gtk_scrolled_window_new (NULL, NULL);
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled), GTK_POLICY_NEVER, GTK_POLICY_AUTOMATIC);    
    
    gtk_window_set_icon_from_file (GTK_WINDOW(window2),"icon.png",NULL);
       
    gtk_container_add(GTK_CONTAINER(scrolled), myGrid);
    gtk_container_add (GTK_CONTAINER (window2), scrolled);
    gtk_widget_show_all(window2);
      
   return 0;
}

gboolean close_screen(gpointer data)
{
  gtk_widget_destroy((GtkWidget*)data);
  gtk_main_quit ();
  return(FALSE);
}

static gboolean inc_progress(gpointer data)
{
         percent += .1;
        gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(data), percent);
        if (percent < 1.0) 
                return TRUE;
        return FALSE;
}


int Show_Splash_Screen(char* image_name,int time,int width,int height)
{
  GtkWidget  *image, *window, *progress, *vbox ;
  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_widget_set_size_request (window, width, height);
  gtk_window_set_decorated(GTK_WINDOW (window), FALSE);
  gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER_ALWAYS);
  gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
  progress = gtk_progress_bar_new();
  g_timeout_add(400, inc_progress, progress); 
  image=gtk_image_new_from_file(image_name);
  vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
  gtk_box_pack_start(GTK_BOX(vbox), image, 1, 1, 0);
  gtk_box_pack_end(GTK_BOX(vbox), progress, 1, 1, 0);
  gtk_container_add(GTK_CONTAINER(window), vbox);
  gtk_widget_show_all (window);
  g_timeout_add (time, close_screen, window);
  gtk_window_set_icon_from_file (GTK_WINDOW(window),"icon.png",NULL);
  gtk_main ();
  return 0;
}
static void
toggle_changed_cb (GtkToggleButton *button,
                   GtkWidget       *popover)
{
  gtk_widget_set_visible (popover,
                          gtk_toggle_button_get_active (button));
}
static GtkWidget *
create_popover (GtkWidget       *parent,
                GtkWidget       *child,
                GtkPositionType  pos)
{
  GtkWidget *popover;

  popover = gtk_popover_new (parent);
  gtk_popover_set_position (GTK_POPOVER (popover), pos);
  gtk_container_add (GTK_CONTAINER (popover), child);
  gtk_container_set_border_width (GTK_CONTAINER (popover), 6);
  gtk_widget_show (child);

  return popover;
}


void advice_page(GtkWidget *calculate, gpointer data){
	GtkWidget *window,*adlabel,*adbutton1,*adbutton2,*adbutton3,*adbutton4,*adbutton5,*adbutton6,*adbutton7,*adgrid;
	GtkWidget *pop1,*pop2,*pop3,*pop4,*pop5,*pop6,*pop7;
	window3 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_widget_set_name(window3,"window3");
    
    gtk_window_set_default_size(GTK_WINDOW(window3), 500, 500);
    gtk_window_set_title (GTK_WINDOW (window3), "Advice");
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file_at_scale("advice.png",550,350,1, NULL );
		adlabel = gtk_image_new_from_pixbuf(pixbuf);
     
    adgrid = gtk_grid_new();
    gtk_widget_set_name(adgrid,"adgrid");
    adbutton1 = gtk_toggle_button_new_with_label ("วิ่งจ๊อกกิ้ง");
    adbutton2 = gtk_toggle_button_new_with_label ("เดิน");
    adbutton3 = gtk_toggle_button_new_with_label ("ปั่นจักรยาน");
    adbutton4 = gtk_toggle_button_new_with_label ("ฟุตบอล");
    adbutton5 = gtk_toggle_button_new_with_label ("ว่ายน้ำ");
    adbutton6 = gtk_toggle_button_new_with_label ("ต่อยมวย");
    adbutton7 = gtk_toggle_button_new_with_label ("แบตมินตัน ");
  
    pop1 = create_popover (adbutton1,gtk_label_new ("500 cal/hr"),GTK_POS_TOP);
    pop2 = create_popover (adbutton2,gtk_label_new ("200 cal/hr"),GTK_POS_TOP);
    pop3 = create_popover (adbutton3,gtk_label_new ("750 cal/hr"),GTK_POS_TOP);
    pop4 = create_popover (adbutton4,gtk_label_new ("800 cal/hr"),GTK_POS_TOP);
    pop5 = create_popover (adbutton5,gtk_label_new ("750 cal/hr"),GTK_POS_TOP);
    pop6 = create_popover (adbutton6,gtk_label_new ("640 cal/hr"),GTK_POS_TOP);
    pop7 = create_popover (adbutton7,gtk_label_new ("520 cal/hr"),GTK_POS_TOP);

    gtk_popover_set_modal (GTK_POPOVER (pop1), FALSE);
    gtk_popover_set_modal (GTK_POPOVER (pop2), FALSE);
    gtk_popover_set_modal (GTK_POPOVER (pop3), FALSE);
    gtk_popover_set_modal (GTK_POPOVER (pop4), FALSE);
    gtk_popover_set_modal (GTK_POPOVER (pop5), FALSE);
    gtk_popover_set_modal (GTK_POPOVER (pop6), FALSE);
    gtk_popover_set_modal (GTK_POPOVER (pop7), FALSE);
      g_signal_connect (adbutton1, "toggled",G_CALLBACK (toggle_changed_cb), pop1);
      g_signal_connect (adbutton2, "toggled",G_CALLBACK (toggle_changed_cb), pop2);
      g_signal_connect (adbutton3, "toggled",G_CALLBACK (toggle_changed_cb), pop3);
      g_signal_connect (adbutton4, "toggled",G_CALLBACK (toggle_changed_cb), pop4);
      g_signal_connect (adbutton5, "toggled",G_CALLBACK (toggle_changed_cb), pop5);
      g_signal_connect (adbutton6, "toggled",G_CALLBACK (toggle_changed_cb), pop6);
      g_signal_connect (adbutton7, "toggled",G_CALLBACK (toggle_changed_cb), pop7);

    gtk_grid_attach(GTK_GRID(adgrid), adlabel, 0, 0, 3, 1);
    gtk_grid_attach(GTK_GRID(adgrid), adbutton1, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(adgrid), adbutton2, 1, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(adgrid), adbutton3, 2, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(adgrid), adbutton4, 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(adgrid), adbutton5, 1, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(adgrid), adbutton6, 2, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(adgrid), adbutton7, 1, 3, 1, 1);
    gtk_grid_set_column_spacing(GTK_GRID(adgrid),20);
    gtk_grid_set_row_spacing(GTK_GRID(adgrid),20);
    gtk_widget_set_halign(adgrid,GTK_ALIGN_CENTER);
    gtk_widget_set_valign(adgrid,GTK_ALIGN_CENTER);


    g_signal_connect (window3, "destroy", 
        G_CALLBACK(close_ad), NULL);
    gtk_container_add (GTK_CONTAINER (window3), adgrid);
    gtk_widget_show_all(window3);




}


void bmiresults(){

	if (bmi > 30){
		strcpy(text,"อ้วนมาก\nค่อนข้างอันตราย เพราะเข้าเกณฑ์อ้วนมาก เสี่ยงต่อการเกิดโรคร้ายแรงที่\nแฝงมากับความอ้วนหากค่า BMI อยู่ในระดับนี้\n"\
			        "จะต้องระวังการรับประทานไขมัน และควรออกกำลังกายอย่างสม่ำเสมอ\nและหากเลขยิ่งสูงกว่า 40.0 ยิ่งแสดงถึงความอ้วนที่มากขึ้น");
		GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file_at_scale("picmorefat.png",800,500,1, NULL );
		bmiimage = gtk_image_new_from_pixbuf(pixbuf);
	}
	else if (bmi >= 25.0 && bmi <= 29.9)
	{
		strcpy(text,"อ้วน\nคุณอ้วนในระดับหนึ่ง ถึงแม้จะไม่ถึงเกณฑ์ที่ถือว่าอ้วนมาก ๆ แต่ก็ยังมีความเสี่ยงต่อการเกิดโรค\nที่มากับความอ้วนได้เช่นกัน ทั้งโรคเบาหวาน และความดันโลหิตสูง");
	    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file_at_scale("picfat.png",700,550,1, NULL );
	    bmiimage = gtk_image_new_from_pixbuf(pixbuf);
	}
	else if (bmi >= 23.0 && bmi <=24.9){
		strcpy(text,"น้ำหนักเกิน\nพยายามอีกนิดเพื่อลดน้ำหนักให้เข้าสู่ค่ามาตรฐาน เพราะค่า BMI \nในช่วงนี้ยังถือว่าเป็นกลุ่มผู้ที่มีความอ้วนอยู่บ้าง\n"\
			        "แม้จะไม่ถือว่าอ้วน แต่หากประวัติคนในครอบครัวเคยเป็น\nโรคเบาหวานและความดันโลหิตสูง ก็ถือว่ายังมีความเสี่ยงมากกว่าคนปกติ");
		GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file_at_scale("picmore.png",800,570,1, NULL );
	    bmiimage = gtk_image_new_from_pixbuf(pixbuf);
	}
	else if (bmi >= 18.6 && bmi <= 22.9){
		strcpy(text,"น้ำหนักปกติ เหมาะสม\nน้ำหนักที่เหมาะสมสำหรับคนไทยคือค่า BMI ระหว่าง 18.5-22.9\nจัดอยู่ในเกณฑ์ปกติ ห่างไกลโรคที่เกิดจากความอ้วน\n"\
			        "และมีความเสี่ยงต่อการเกิดโรคต่าง ๆ น้อยที่สุด \nควรพยายามรักษาระดับค่า BMI ให้อยู่ในระดับนี้ให้นานที่สุด");
		GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file_at_scale("picnormal.png",700,550,1, NULL );
	    bmiimage = gtk_image_new_from_pixbuf(pixbuf);
	}
	else if(bmi >= 0 && bmi <= 18.5){
		strcpy(text,"ผอมเกินไป\nน้ำหนักน้อยกว่าปกติก็ไม่ค่อยดี หากคุณสูงมากแต่น้ำหนักน้อยเกินไป\nอาจเสี่ยงต่อการได้รับสารอาหารไม่เพียงพอหรือได้รับพลังงานไม่เพียงพอ\n"\
			        "ส่งผลให้ร่างกายอ่อนเพลียง่าย การรับประทานอาหารให้เพียงพอ\nและการออกกำลังกายเพื่อเสริมสร้างกล้ามเนื้อสามารถช่วยเพิ่มค่า BMI ให้อยู่ในเกณฑ์ปกติได้");
	    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file_at_scale("pictiny.png",700,550,1, NULL );
	    bmiimage = gtk_image_new_from_pixbuf(pixbuf);
	}
	else{
		strcpy(text,"EROR!!! กรุณากรอกข้อมูลให้ครบถ้วน");
	}
	
}

int assistant2 (int argc,
          char *argv[])
{
  GtkWidget *window, *label2, *button, *myGrid, *overlay, *box,*button1,*button2 ;
  GtkWidget *entry, *label, *test, *bmical,*test2,*mealLabel,*label3,*label4, *advice;
  
  guint i;
  

  gtk_init (&argc, &argv);

  
  assistant = gtk_assistant_new ();
  gtk_widget_set_size_request (assistant, 800, 700);
  gtk_window_set_title (GTK_WINDOW (assistant), "CalDic(tionary)");
  g_signal_connect (G_OBJECT (assistant), "destroy",
                    G_CALLBACK (gtk_main_quit), NULL);
  char buffer[32];
    snprintf(buffer, sizeof(buffer), "Your BMI is:%.2f", bmi);
    

  page[0].widget = gtk_grid_new();
  page[1].widget = gtk_overlay_new();
  page[2].widget = gtk_grid_new();
  page[3].widget = gtk_grid_new();
  bmical = gtk_label_new(buffer);
  //gtk_label_set_text(GTK_LABEL(bmical),);
  gtk_grid_attach(GTK_GRID(page[0].widget), bmical, 1, 0, 1, 1);
  gtk_grid_attach(GTK_GRID(page[0].widget), bmiimage, 1, 1, 1, 1);
  test2 = gtk_label_new(text);
  gtk_widget_set_name(test2,"test");
  gtk_widget_set_name(bmical,"bmi");
  
  gtk_grid_attach(GTK_GRID(page[0].widget), test2, 2, 1, 1, 1);

  box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
  gtk_widget_set_name(box,"box");
  mealLabel = gtk_label_new("  choose your meal");
        button1 = gtk_button_new_with_label("Breakfast");
        
        button2 = gtk_button_new_with_label("Lunch");
        gtk_overlay_add_overlay (GTK_OVERLAY (page[1].widget), box);
        gtk_box_pack_start(GTK_BOX(box), mealLabel, 1, 1, 3);
        gtk_box_pack_start(GTK_BOX(box), button1, 1, 1, 0);
        gtk_widget_set_sensitive(button1,TRUE);
        gtk_box_pack_start(GTK_BOX(box), button2, 1, 1, 0);
        
        gtk_widget_set_halign (box, GTK_ALIGN_START);
        gtk_widget_set_valign (box, GTK_ALIGN_START);
      
        
        
        GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file_at_scale("calorie.png",650,450,1, NULL );
		label = gtk_image_new_from_pixbuf(pixbuf);
      
        label2 = gtk_label_new("ที่ร่างกายต้องการในแต่ละวัน");
        gtk_widget_set_name(label2,"textlabel");
        gtk_widget_set_margin_bottom(label2,50);
        if (gender_check == 1)
        {
        	label3 = gtk_label_new("Male  1800-2500 Kcal");
        }
        else if (gender_check == 2)
        {
        	label3 = gtk_label_new("Female  1500-2000 Kcal");
        }
        gtk_widget_set_name(label3,"recolabel");
        
        
        button = gtk_button_new_with_label("Dinner");
        g_signal_connect(button, "clicked", G_CALLBACK(choosefood), "Dinner");
        g_signal_connect(button1, "clicked", G_CALLBACK(choosefood), "Breakfast");
        g_signal_connect(button2, "clicked", G_CALLBACK(choosefood), "Lunch");
        myGrid = gtk_grid_new();
        gtk_grid_attach (GTK_GRID (myGrid), label, 0, 0, 1, 1);
        
        gtk_grid_attach (GTK_GRID (myGrid), label2, 0, 1, 1, 1);
        gtk_grid_attach (GTK_GRID (myGrid), label3, 0, 2, 1, 1);
      
        gtk_box_pack_start(GTK_BOX(box), button, 1, 1, 0);
        gtk_widget_set_halign(myGrid,GTK_ALIGN_CENTER);
        gtk_widget_set_valign(myGrid,GTK_ALIGN_START);
        
        gtk_container_add(GTK_CONTAINER(page[1].widget),myGrid);
        gtk_widget_set_name(page[2].widget,"totalbox");
        gtk_widget_set_halign(page[2].widget,GTK_ALIGN_CENTER);
        gtk_widget_set_valign(page[2].widget,GTK_ALIGN_CENTER);
        gtk_grid_set_column_spacing(GTK_GRID(page[2].widget),20);



        label5 = gtk_label_new("Breakfast:");
        label6 = gtk_label_new("Lunch:");
        label7 = gtk_label_new("Dinner:");
       
        
        label8 = gtk_label_new(buffer1);
        label9 = gtk_label_new(buffer2);
        label10 = gtk_label_new(buffer3);
        label11 = gtk_label_new("Total:");
        gtk_widget_set_name(label11,"total");
        
        label12 = gtk_label_new(buffer4);
        gtk_grid_attach (GTK_GRID (page[2].widget), label5, 0, 0, 1, 1);
        gtk_grid_attach (GTK_GRID (page[2].widget), label6, 0, 1, 1, 1);
        gtk_grid_attach (GTK_GRID (page[2].widget), label7, 0, 2, 1, 1);
        gtk_grid_attach (GTK_GRID (page[2].widget), label11, 0, 3, 1, 1);
         gtk_grid_attach (GTK_GRID (page[2].widget), label8, 1, 0, 1, 1);
         gtk_grid_attach (GTK_GRID (page[2].widget), label9, 1, 1, 1, 1);
         gtk_grid_attach (GTK_GRID (page[2].widget), label10, 1, 2, 1, 1);
         gtk_grid_attach (GTK_GRID (page[2].widget), label12, 1, 3, 1, 1);


        GdkPixbuf *pixbuf2 = gdk_pixbuf_new_from_file_at_scale("total.png",650,450,1, NULL );
		label13 = gtk_image_new_from_pixbuf(pixbuf2);
    
        text1 = gtk_label_new("แคลอรี่รวม = ");
        text2 = gtk_label_new("แคลอรี่ที่ควรได้รับต่อวัน = ");
        text3= gtk_label_new("แคลอรี่ที่เกิน = ");
        label14 = gtk_label_new(buffer4);
        label15 = gtk_label_new(gender);
        label16 = gtk_label_new(overcal);
        advice = gtk_button_new_with_label("advice");
        gtk_widget_set_name(page[3].widget,"sumbox");
        gtk_widget_set_halign(page[3].widget,GTK_ALIGN_CENTER);
        gtk_widget_set_valign(page[3].widget,GTK_ALIGN_CENTER);
        gtk_widget_set_margin_bottom(label13,20);
        gtk_widget_set_margin_bottom(label16,20);

        gtk_grid_attach (GTK_GRID (page[3].widget), label13, 0, 0, 3, 1);
        gtk_grid_attach (GTK_GRID (page[3].widget), text1, 0, 1, 1, 1);
        gtk_grid_attach (GTK_GRID (page[3].widget), text2, 0, 2, 1, 1);
        gtk_grid_attach (GTK_GRID (page[3].widget), text3, 0, 3, 1, 1);
        gtk_grid_attach (GTK_GRID (page[3].widget), label14, 2, 1, 1, 1);
        gtk_grid_attach (GTK_GRID (page[3].widget), label15, 2, 2, 1, 1);
        gtk_grid_attach (GTK_GRID (page[3].widget), label16, 2, 3, 1, 1);
        gtk_grid_attach (GTK_GRID (page[3].widget), advice, 0, 4, 3, 1);
         g_signal_connect (G_OBJECT (advice), "clicked",
                    G_CALLBACK (advice_page), NULL);

  
  


  for (i = 0; i < 4; i++)
  {
    page[i].index = gtk_assistant_append_page (GTK_ASSISTANT (assistant),
                                               page[i].widget);
    gtk_assistant_set_page_title (GTK_ASSISTANT (assistant),
                                  page[i].widget, page[i].title);
    gtk_assistant_set_page_type (GTK_ASSISTANT (assistant),
                                  page[i].widget, page[i].type);
    gtk_assistant_set_page_complete (GTK_ASSISTANT (assistant),
                                     page[i].widget, page[i].complete);
  }

  
  
  g_signal_connect (G_OBJECT (assistant), "cancel",
                    G_CALLBACK (assistant_cancel), NULL);
  g_signal_connect (G_OBJECT (assistant), "close",
                    G_CALLBACK (assistant_close), NULL);
  gtk_widget_show_all (assistant);
  gtk_main ();
  return 0;
}

static void
meal_check (GtkEditable *entry,
               GtkAssistant *assistant)
{
	gint num = gtk_assistant_get_current_page (assistant);
  
  if (luach_check == TRUE && din_check == TRUE && break_check == TRUE)
  {
  	gtk_assistant_set_page_complete (assistant, page[1].widget, TRUE);
  } 
}

static void
assistant_cancel (GtkAssistant *assistant,
                  gpointer data)
{
  gtk_widget_destroy (GTK_WIDGET (assistant));
}


static void
assistant_close (GtkAssistant *assistant,
                 gpointer data)
{
  
  gtk_widget_destroy (GTK_WIDGET (assistant));
}

static void
bmi_insert_data (GtkButton *button,
                            gchar *data)
{
  GtkWidget *content_area;
  GtkWidget *dialog;
  GtkWidget *hbox;
  GtkWidget *image;
  GtkWidget *table;
  GtkWidget *weight;
  GtkWidget *height;
  GtkWidget *label;
  gint response;

  if (strcmp(data,"male") == 0)
  {
  	gender_check = 1; 	
  }
  else if (strcmp(data, "female") == 0){
  	gender_check = 2;
  }

  dialog = gtk_dialog_new_with_buttons ("BMI Calculate",
                                        GTK_WINDOW (window),
                                        GTK_DIALOG_MODAL| GTK_DIALOG_DESTROY_WITH_PARENT,
                                        _("_OK"),
                                        GTK_RESPONSE_OK,
                                        "_Cancel",
                                        GTK_RESPONSE_CANCEL,
                                        NULL);

  content_area = gtk_dialog_get_content_area (GTK_DIALOG (dialog));
  hbox = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 8);
  gtk_container_set_border_width (GTK_CONTAINER (hbox), 8);
  gtk_box_pack_start (GTK_BOX (content_area), hbox, FALSE, FALSE, 0);
  image = gtk_image_new_from_icon_name ("face-smile", GTK_ICON_SIZE_DIALOG);
  gtk_box_pack_start (GTK_BOX (hbox), image, FALSE, FALSE, 0);
  table = gtk_grid_new ();
  gtk_grid_set_row_spacing (GTK_GRID (table), 4);
  gtk_grid_set_column_spacing (GTK_GRID (table), 4);
  gtk_box_pack_start (GTK_BOX (hbox), table, TRUE, TRUE, 0);
  label = gtk_label_new_with_mnemonic ("_กรอกน้ำหนัก(กิโลกรัม)");
  gtk_grid_attach (GTK_GRID (table), label, 0, 0, 1, 1);
  weight = gtk_entry_new ();
  gtk_grid_attach (GTK_GRID (table), weight, 1, 0, 1, 1);
  gtk_label_set_mnemonic_widget (GTK_LABEL (label), weight);
  label = gtk_label_new_with_mnemonic ("ก_รอกส่วนสูง(เซ็นติเมตร)");
  gtk_grid_attach (GTK_GRID (table), label, 0, 1, 1, 1);
  height = gtk_entry_new ();;
  gtk_grid_attach (GTK_GRID (table), height, 1, 1, 1, 1);
  gtk_label_set_mnemonic_widget (GTK_LABEL (label), height);

  gtk_widget_show_all (hbox);
  response = gtk_dialog_run (GTK_DIALOG (dialog));

  if (response == GTK_RESPONSE_OK)
    {
      num1 = atoi((char *)gtk_entry_get_text(GTK_ENTRY(weight)));
      float num2 = strtof((char *)gtk_entry_get_text(GTK_ENTRY(height)),NULL);
      num2 = num2/100;
      bmi = num1/(num2*num2);
      bmiresults();
      g_signal_connect(dialog, "destroy", 
        G_CALLBACK(assistant2), NULL);
    }

  gtk_widget_destroy (dialog);
}


int main(int argc, char *argv[])
{
    GtkWidget *window, *bmiLabel, *maleButton, *maleLabel, *femaleButton, *femaleLabel, *myGrid, *maleImage, *femaleImage;
    GdkPixbuf *pixbuf3 = gdk_pixbuf_new_from_file_at_scale("box.png",500,300,1, NULL );
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file_at_scale("man-2.png",300,200,1, NULL );
    GdkPixbuf *pixbuf2 = gdk_pixbuf_new_from_file_at_scale("girl-1.png",300,200,1, NULL );
    /*---- CSS ------------------*/
    GtkCssProvider *provider;
    GdkDisplay *display;
    GdkScreen *screen;
    /*---------------------------*/

    gtk_init(&argc, &argv);
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_name(window,"window");
    gtk_window_set_title(GTK_WINDOW(window), "CalDic(tionary)");
    gtk_window_set_default_size(GTK_WINDOW(window), 200, 250);
    Show_Splash_Screen("1.png",5000,100,100);
    gtk_window_set_icon_from_file (GTK_WINDOW(window),"icon.png",NULL);
    csv_read();

    myGrid = gtk_grid_new();
    gtk_widget_set_name(myGrid,"myGrid");

    bmiLabel = gtk_image_new_from_pixbuf(pixbuf3);
    
    gtk_widget_set_name(bmiLabel,"bmiLabel");


    maleButton = gtk_button_new();
    maleLabel = gtk_label_new("Male");
    gtk_widget_set_name(maleLabel,"maleLabel");
    maleImage = gtk_image_new_from_pixbuf(pixbuf);
    gtk_button_set_image (GTK_BUTTON (maleButton), maleImage);
    g_signal_connect(maleButton, "clicked", 
        G_CALLBACK(bmi_insert_data), "male");

    femaleButton = gtk_button_new();
    femaleLabel = gtk_label_new("Female");
    femaleImage = gtk_image_new_from_pixbuf(pixbuf2);
    gtk_button_set_image (GTK_BUTTON (femaleButton), femaleImage);
    g_signal_connect(femaleButton, "clicked", 
        G_CALLBACK(bmi_insert_data), "female");

    gtk_grid_attach(GTK_GRID(myGrid), bmiLabel, 3, 0, 3, 1);
    gtk_grid_attach(GTK_GRID(myGrid), maleButton, 3, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(myGrid), maleLabel, 3, 4, 1, 1);
    gtk_grid_attach(GTK_GRID(myGrid), femaleButton, 5, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(myGrid), femaleLabel, 5, 4, 1, 1);
    gtk_widget_set_margin_bottom(bmiLabel,100);
    
    gtk_widget_set_halign(myGrid,GTK_ALIGN_CENTER);
    gtk_widget_set_valign(myGrid,GTK_ALIGN_CENTER);



    g_signal_connect (window, "destroy", 
        G_CALLBACK(gtk_main_quit), NULL);

    /* ----------------- CSS ----------------------------------------------------------------------------------------------*/
    provider = gtk_css_provider_new ();
    display = gdk_display_get_default ();
    screen = gdk_display_get_default_screen (display);
    gtk_style_context_add_provider_for_screen (screen, GTK_STYLE_PROVIDER (provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    
    const gchar* home = "CalDicstyle.css";
    
    GError *error = 0;
    
    gtk_css_provider_load_from_file(provider, g_file_new_for_path(home), &error);
    g_object_unref (provider);
/* --------------------------------------------------------------------------------------------------------------------*/

    gtk_container_add(GTK_CONTAINER (window), myGrid);
    gtk_widget_show_all(window);

    gtk_main();
    return(0);
}