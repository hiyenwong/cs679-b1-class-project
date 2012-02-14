var NS4 = (document.layers); // Which browser?
var IE4 = (document.all); 
var win = window; // window to search. 
var n = 0;
function findInPage(str)
{
  var txt, i, found; 
  if (str == "")
    return false;
    
/*  if (NS4)
  { 
    if (!win.find(str))
      while(win.find(str, false, true)) 
        n++;
    else 
      n++; // If not found in either direction, give message. 
      
  }	*/
  if (IE4)
  {
    txt = win.document.body.createTextRange(); 
    for (i = 0; i <= n && (found = txt.findText(str)) != false; i++)
    {
      txt.moveStart("character", 1);
      txt.moveEnd("textedit"); 
    }
    
    if (found)
    {
      txt.moveStart("character", -1);
      txt.findText(str); 
      txt.select();
      txt.scrollIntoView();
      n++;
    }
    else
    {
      if(n > 0)
      {
        n = 0;
        findInPage(str); 
      } // Not found anywhere, give message. else alert("Not found.");
    }
  }
  
  else if(NS4)
  { 
    if (!win.find(str))
    {
      while(win.find(str, false, true))
      {
        n++;
      }
    }
    else 
      n++; // If not found in either direction, give message. 
      
  }
  
  else
  {
  	if (n > 0)
	{
		n = 0;
		findinpage(str);
	}
  }
  
  return false;
}