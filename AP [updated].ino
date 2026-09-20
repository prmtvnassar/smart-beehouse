#include <WiFi.h>
#include <WebServer.h>

// Replace with your network credentials (AP)
//const char* ssid = "Vodafone_VDSL_E5B5";
//const char* password = "TDE89F44WBQTJ";

const char* ssid = "Esp_Server";
const char* password = "12345678";

const char* host = "192.168.1.120";
const int port = 8088;

WebServer server(80);
IPAddress IP(192,168,1,128);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);


uint8_t data[60]; 
uint8_t data_temp[60]; 

uint8_t HivNo[5];
uint8_t HivIP[20];
uint8_t To[6];
uint8_t humi[15];
uint8_t Ti[15];
uint8_t Wi[5];
uint8_t Fs[3];
uint8_t Hs[3];



void setup() {
Serial.begin(115200);
  
 // Connect to Wi-Fi network with SSID and password
 // Serial.print("Setting AP (Access Point)…");

  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(IP, gateway, subnet);
  
  IPAddress IP = WiFi.softAPIP();
  Serial.print("Access Point started with IP address: ");
  Serial.println(IP);
  Serial.print("connecting to ");
  Serial.println(host);
  server.begin();
  server.on("/", OnConnect);
  server.onNotFound(NotFound); 
  Serial.println("HTTP Server started!");
  
}

void loop() {
  server.handleClient();
      /* Use WiFiClient class to create TCP connections */
    WiFiClient client;
    
    //bool connectionStat=client.connect(host, port, 2000);   
    if (! client.connect(host, port))
    {
    delay(2000);
        Serial.println("connection to station failed");
        return;
    }
    else
    {

    // This will send the data to the server 
    client.print("Please send sensors data");
    delay(100);


    int len = client.readBytes(data, 60);
    
    if(len<60){
      data[len] = '\0';
    }
    else
    {data[59] = '\0';
    }
    
 Serial.println("Received bytes:");
 Serial.println(len);


 for (int i = 0; i <= len-1; i++) { 
      Serial.print((char)data[i]);
   }
  //delay(100);



Serial.println("Hiv No.: ");
    HivNo[0]=data[0];
    HivNo[1]=data[1];
    HivNo[2]=data[2];
    HivNo[3]=0;
Serial.println((char*)HivNo);


Serial.println("HiveIP: ");
    HivIP[0]=data[5];
    HivIP[1]=data[6];
    HivIP[2]=data[7];
    HivIP[3]=data[8];
    HivIP[4]=data[9];
    HivIP[5]=data[10];
    HivIP[6]=data[11];
    HivIP[7]=data[12];
    HivIP[8]=data[13];
    HivIP[9]=data[14];
    HivIP[10]=data[15];
    HivIP[11]=data[16];
    HivIP[12]=data[17];
    HivIP[13]=0;
Serial.println((char*)HivIP);    


Serial.println("To: ");
    To[0]=data[20];
    To[1]=data[21];
    To[2]=data[22];
    To[3]=data[23];
    To[4]=data[24];   
    To[5]=0;
Serial.println((char*)To);



Serial.println("Humi: ");
    humi[0]=data[27];
    humi[1]=data[28];
    humi[2]=data[29];
    humi[3]=data[30];
    humi[4]=data[31];
    humi[5]=0;  
Serial.println((char*)humi);    



Serial.println("Ti: ");
    Ti[0]=data[34];
    Ti[1]=data[35];
    Ti[2]=data[36];
    Ti[3]=data[37];
    Ti[4]=data[38];   
    Ti[5]=0;
Serial.println((char*)Ti);


Serial.println("Wi: ");
    Wi[0]=data[41];
    Wi[1]=data[42];
    Wi[2]=data[43];
    Wi[3]=data[44];
    Wi[4]=data[45];   
    Wi[5]=0;
Serial.println((char*)Wi);


Serial.println("Fs: ");
    Fs[0]=data[48];
    Fs[1]=0;  
Serial.println((char*)Fs);    
//delay(100);


Serial.println("Hs: ");
    Hs[0]=data[51];
    Hs[1]=0;
Serial.println((char*)Hs);    
//delay(100);


// can we see it now?  //No, we can't :<<
client.stop();
    } 
     

}
                                

void OnConnect()
{
server.send(200, "text/html", getPage());  //getPage()
}

void NotFound()
{
  server.send(404, "text/plain","Not Found :/" );  //
}


String getPage()
{
  String page = "<html lang=\"en\"><head><meta http-equiv='refresh' content='5'/>";
  page += "<title>ESP32 WebServer</title>";
  page += "</head>";
  page+= "<body bgcolor=#FFFFFF>";
  page+= "<p align=center> &nbsp; </p>";
  page+= "<p align=center> <b>  <font color=#8B8000 size=11%>Bees Hotel </font> <b>  </p>";
  page+= "<p align=center> <b> <font color=#8B8000  size=9%>   Sensors Monitor  </font> <b> </p>";
  page+= "<p align=center> &nbsp; </p>";
  page+= "<p align=center>";


  page+= "<table border=0 width=80%>";
  //*************************************************************************************************
  page+=	"<tr align=center   style=height: 15%>";
  page+= "<td style=background-color:#D9D9D9>";
  page+= "<img  src='data:image/bmp;base64,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'];function LoadImagesAndRender(){var loadedImages=0;for(var i=0;i<images.length;i++){var source=images[i];images[i]=new Image();images[i].src=source;images[i].onload=function(){loadedImages++;if (loadedImages==images.length){Render();}};}}function Render(){let a=document.getElementById('1edf16fc9e8c4a01811ea987fc9e1767');let b=a.getContext('2d');a.width=64;a.height=64;b.drawImage(images[0],0,0,64,64,0,0,64,64);}window.addEventListener('onload',LoadImagesAndRender());>";
  page+= "</td>";
  page+= "<td style=background-color:#D9D9D9>";
  page+= "<p align=center><font size=7%>  Hive No. </font> </p>";
  page+= "</td>";
  page+= "<td style=background-color:#D9D9D9  width: 60%>";  
  page+= "<font color=#000000 size=7%>";
  page+= (char*)HivNo;
  page+= "</font>";
  page+= "</td>";
  page+=	"</tr>";
  //*************************************************************************************************
  page+=	"<tr align=center   style=height: 15%>";
  page+= "<td style=background-color:#D9D9D9>";
  page+= "<img  src='data:image/bmp;base64,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'];function LoadImagesAndRender(){var loadedImages=0;for(var i=0;i<images.length;i++){var source=images[i];images[i]=new Image();images[i].src=source;images[i].onload=function(){loadedImages++;if (loadedImages==images.length){Render();}};}}function Render(){let a=document.getElementById('1edf16fc9e8c4a01811ea987fc9e1767');let b=a.getContext('2d');a.width=64;a.height=64;b.drawImage(images[0],0,0,64,64,0,0,64,64);}window.addEventListener('onload',LoadImagesAndRender());>";
  page+= "</td>";
  page+= "<td style=background-color:#D9D9D9>";
  page+= "<p align=center><font size=7%>  Hive IP. </font> </p>";
  page+= "</td>";
  page+= "<td style=background-color:#D9D9D9  width: 60%>";  
  page+= "<font color=#000000 size=7%>";
  page+= (char)data[5];
  page+= (char)HivIP[1];
  page+= (char)HivIP[2];
  page+= (char)HivIP[3];
  page+= (char)HivIP[4];
  page+= (char)HivIP[5];
  page+= (char)HivIP[6];
  page+= (char)HivIP[7];
  page+= (char)HivIP[8];
  page+= (char)HivIP[9];
  page+= (char)HivIP[10];
  page+= (char)HivIP[11];
  page+= (char)HivIP[12];
  page+= (char)HivIP[13];

  page+= "</font>";
  page+= "</td>";
  page+=	"</tr>";
  //*************************************************************************************************
  page+=	"<tr align=center   style=height: 15%>";
  page+= "<td style=background-color:#D9D9D9>";
  page+= "<img  src='data:image/bmp;base64,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'];function LoadImagesAndRender(){var loadedImages=0;for(var i=0;i<images.length;i++){var source=images[i];images[i]=new Image();images[i].src=source;images[i].onload=function(){loadedImages++;if (loadedImages==images.length){Render();}};}}function Render(){let a=document.getElementById('1edf16fc9e8c4a01811ea987fc9e1767');let b=a.getContext('2d');a.width=64;a.height=64;b.drawImage(images[0],0,0,64,64,0,0,64,64);}window.addEventListener('onload',LoadImagesAndRender());>";
  page+= "</td>";
  page+= "<td style=background-color:#D9D9D9>";
  page+= "<p align=center><font size=7%>  TempOut </font> </p>";
  page+= "</td>";
  page+= "<td style=background-color:#D9D9D9  width: 60%>";  
  page+= "<font color=#000000 size=7%>";
  page+= (char)data[20];
  page+= (char)data[21];
  page+= (char)data[22];
  page+= (char)data[23];
  page+= (char)data[24];
  page+= "</font>";
  page+= "<font color=#000000 size=7%> C</font>";
  page+= "</td>";
  page+=	"</tr>";
  //*************************************************************************************************
  page+= "<tr align=center   style=height: 15%>";
  page+= "<td>";
  page+= "<img src='data:image/bmp;base64,iVBORw0KGgoAAAANSUhEUgAAAEAAAABACAYAAACqaXHeAAAAAXNSR0IArs4c6QAAAARnQU1BAACxjwv8YQUAAAAJcEhZcwAADsMAAA7DAcdvqGQAAAZDSURBVHhexZvdaxxVGMZTFQQFRS8UizXZbRH/AL/AGwVB0apYrIItiojQKz9aQVSQ4pXghVDdXQOCYm5sKkpSijVqa8H6USUi6UWl2kRj1xTbmJ2Z3WzS0OP7bDbmzNlnZ87snJlc/MLyzDnv+zyzM7OzZyd9Sqk1oVD2HixU/OkW8pqNyQMqZk3xHe/GQtlvCKpNAxobmzVUzJK+3eqigbJ/VAvfAhq2sTlZQsUsKZaDnWb4FbCNzckSKmYFOfRNcj8VqJgF3Q59k7xPBSpmQdShb5LnqUBF1wwMejdJsKhD36SBOayWa6jokvWD6jIJNGEEtGECc1lNl1DRJXKTM0TCWeINsZouoaIr5IK2gwezBzVYbVdQ0QXFd+s3S4CmGagHmqjFeriAimm5/r3a1XL4TpEwPeJNoSbrlRYqpkH+rBsoeQd4kN5BTdRmPdNAxTQUSv6rLIATpDbrmQYq9kp/yb9LjC51GHfHEnqw3r1CxV7oH6xfJ+/QDDHtFumBXsxDL1AxKX3D6uJCxT9CDWeB9EJP5iUpVEyK3Lu/QY1mCHoyL0mhYhKKFW+zGLpgGsyBC+jNPCWBirZseLu+XozMGsbyZBYemDdbqGhLoRyMElM5E4wyb7ZQ0QY5Bx/nhvIHXphHG6gYx8aKf400PmsaWUPOwhPzGgcV45CGw4aBDsSQeu1IQ3092VT/+Ist8BoatrE5KRlmXuOgYhTFkr+FNA9xx4eB+uGvplpcXKRgG8awuWmAN+Y5Cip2Y9Oec1fE3e3h3f1+unv4FTDG+ZEg3uCRee8GFbtRqAS7aGONVw43aGAGxrIaqRCPzHs3qMho3e5afMcf+z387uO8v+ejQN0rfPNHeBvGsho6Tx+oq4mZBXVc2DZSp2PCeFNJbpOpyJDiWzubdVKtLYRC3rd39VzfPByEtmGsPtfk2bG6ml9YHf/L39HjNbayDAwqMuT8+pY06mD63/AOeGjf6g7Y8nE9tA1j9bk6Znjw02nLHSBeWQYGFU0GyrXbaSPCwZPhwxwXu0c+qatHhR+NTwaMZTWeG2uophF+vrmontxvcwosA88siwkVTWSP7mVNGC9+aX8RxFhzfrfwOz6zD99CPLMsJlTUufbNmcul4PmOBhEclgufHoCBMeY8Z+GXOQ/vLJMOFXXkPvtuUjySW94P1KFT3XcCtmGMPud5t+FbwDvLpENFHTmUXmfFbUCo/b821alzCy3wGhob5zp8C/HOMulQUUeKjNHijsgsPBDvLJMOFXUGyv5xWtwBL3yRYXgB3lkmHSrqSKEzZmEXZB2+zRmWSYeKK8ifdVLE+Tp/TuHBEjKwbCtQUUeKuPiB83925hceNFkmHSrqFMrBJCncEzmHF4JJlkmHijp4aIkXT0b+4ZcfuGKZdKioI4Vil7/i2CW3vHmHbxO7TEZFnWLZf4sUtsY2fBZriPDOMulQUae/4j3MittgG/62DwJ19M/ut87YhjH6HBvgnWXSoaJO+ymvJI+4tcA3PZvw8i51rBQxMAZj9bkxNGyeMqOiiRQbMYpHYhsevHTI/uszxprzIxhhWUyoaFIse0+RBhSETHLB+/y38LuPdxrrh2wNEWNZDQY8sywmVDS5oTx3lRStmU0YP1fDS2JR4cHpufD4B4ZXz3W81rdhrD43gho8sywmVGTINyurZ3/0HRAXHpg7QF9DxGt9m/UOSPAsERUZ7YthtaOZwWOf1tW47AQsYD4xGh0eHDROge/kio/gAK/1bRjLahhUkzxiS8VuFEreM6RhKtKuIXYgHpn3blCxG+0fR47RxinodQ2xE+9Y0meHqBhF+6mQ2FMhCVgfxF0fCw6wzVxDJFR7eVqEinEUKrVbpeG8YSAVuMnB5zw+6nCxA3gNzeIGaB6emNc4qGhDsRJsI0bWBHhhHm2goi3yfXu7GHC6YJIQ6R1sZ95soWISWj+b5fGEqIn0tP35KwoqJmVjqbFBTI13mMyOcfRkXpJCxV64c7e6BP/dIeacfkIYVNEDvZiHXqBiGnAXJl9EXhazc4b5NMyhZpI7PFuo6ILi4OyVrU+Kir9PAvhGIBt8zEUN1GI9XEBF12zaoy4tlmv34wFnuVsbksP4Kwl4QvDanFjWvCGMwVjMYbXcovr+A6SRQClQPTSiAAAAAElFTkSuQmCC'];function LoadImagesAndRender(){var loadedImages=0;for(var i=0;i<images.length;i++){var source=images[i];images[i]=new Image();images[i].src=source;images[i].onload=function(){loadedImages++;if (loadedImages==images.length){Render();}};}}function Render(){let a=document.getElementById('0ca3fa3eb7ac4d7892a854e589fd4b81');let b=a.getContext('2d');a.width=64;a.height=64;b.drawImage(images[0],0,0,64,64,0,0,64,64);}window.addEventListener('onload',LoadImagesAndRender());>";
  page+= "</td>";
  page+= "<td>";
  page+= "<p align=center><font size=7%>  Humidity </font> </p>";
  page+= "</td>";
  page+=	"<td style=width:70%>";
  page+= "<font color=#000000 size=7%>";
  page+= (char*)humi;  
  page+= "</font> ";
  page+= "  <font color=#000000 size=7%>%</font> "; 
  page+= "</td>";
  page+=	"</tr>";
//*************************************************************************************************
  page+= "<tr align=center   style=height: 15%>";
  page+= "<td style=background-color:#D9D9D9>";
  page+= "<img src='data:image/bmp;base64,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'];function LoadImagesAndRender(){var loadedImages=0;for(var i=0;i<images.length;i++){var source=images[i];images[i]=new Image();images[i].src=source;images[i].onload=function(){loadedImages++;if (loadedImages==images.length){Render();}};}}function Render(){let a=document.getElementById('6580c206607b453c8acc87017795b6fc');let b=a.getContext('2d');a.width=64;a.height=64;b.drawImage(images[0],0,0,64,64,0,0,64,64);}window.addEventListener('onload',LoadImagesAndRender());>";  
  page+="</td>";
  page+= "<td style=background-color:#D9D9D9>";
  page+= "<p align=center><font size=7%>  TempIn </font> </p>";
  page+= "</td>";
  page+=	"<td style=background-color:#D9D9D9  width: 60%>";
  page+= "<font color=#000000 size=7%>";
  
  page+= (char)data[34];
  page+= (char)data[35];
  page+= (char)data[36];
  page+= (char)data[37];
  page+= (char)data[38];
  
  page+= "</font>";
  page+= "<font color=#000000 size=7%> C</font>"; 
  page+= "</td>";
  page+=	"</tr>";
//*************************************************************************************************
  page+= "<tr align=center   style=height: 15%>";
  page+= "<td>";
  page+= "<img src='data:image/bmp;base64,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'];function LoadImagesAndRender(){var loadedImages=0;for(var i=0;i<images.length;i++){var source=images[i];images[i]=new Image();images[i].src=source;images[i].onload=function(){loadedImages++;if (loadedImages==images.length){Render();}};}}function Render(){let a=document.getElementById('cd73f9f78b3a4df0a3e23c1c8a3c957a');let b=a.getContext('2d');a.width=64;a.height=64;b.drawImage(images[0],0,0,64,64,0,0,64,64);}window.addEventListener('onload',LoadImagesAndRender());>";  
  page+="</td>";
  page+= "<td>";
  page+= "<p align=center><font size=7%> weight </font> </p>";
  page+= "</td>";
  page+=	"<td style=width:70%>";
  page+= "<font color=#000000 size=7%>";
  page+= (char*)Wi;  
  page+= "</font>";
  page+= "  <font color=#000000 size=7%>kg</font>  "; 
  page+= "</td>";
  page+=	"</tr>";
//*************************************************************************************************
  page+="<tr align=center   style=height: 15%>";
  page+="<td style=background-color:#D9D9D9>";
  page+="<img src='data:image/png;base64,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'>";  
  page+="</td>";
  page+= "<td style=background-color:#D9D9D9>";
  page+= "<p align=center><font size=7%>  FanStat </font> </p>";
  page+= "</td>";
  page+=	"<td style=background-color:#D9D9D9  width: 60%>";
  page+= "<p align=center>   <font color=#000000 size=7%>";
  page+= (char*)Fs;
  page+= "</font>   </p>";
  page+= "</td>";
  page+=	"</tr>";
//*************************************************************************************************
  page+="<tr align=center style=height: 15%>";
  page+="<td>";
  page+=  "<img src='data:image/png;base64,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'>";
  page+="</td>";
  page+= "<td>";
  page+= "<p align=center><font size=7%> HeaterStat </font> </p>";
  page+= "</td>";
  page+=	"<td style=70%>";
  page+= "<p align=center>   <font color=#000000 size=7%>";
  page+= (char*)Hs;
  page+= "</font>   </p>";
  page+= "</td>";
  page+=	"</tr>";
  page+=  "</table>";
  page+= "</p>";

page+= "</html>";
return page;
}
