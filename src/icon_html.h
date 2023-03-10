String Icon()
{
 // Debug info 
 DebugPrintln(3, "Send favicon.ico");

 String content; 
 // Favorit icon as SVG/XML file
 content +=F( "<svg xmlns='http://www.w3.org/2000/svg' class='icon icon-tabler icon-tabler-access-point' width='44' height='44' viewBox='0 0 24 24' stroke-width='1.5' stroke='#2c3e50' fill='none' stroke-linecap='round' stroke-linejoin='round'>");
 content +=F( "<path stroke='none' d='M0 0h24v24H0z' fill='none'/>");
 content +=F( "<line x1='12' y1='12' x2='12' y2='12.01' />");
 content +=F( "<path d='M14.828 9.172a4 4 0 0 1 0 5.656' />");
 content +=F( "<path d='M17.657 6.343a8 8 0 0 1 0 11.314' />");
 content +=F( "<path d='M9.168 14.828a4 4 0 0 1 0 -5.656' />");
 content +=F( "<path d='M6.337 17.657a8 8 0 0 1 0 -11.314' />");
 content +=F( "</svg>");
  
 return content;
}
