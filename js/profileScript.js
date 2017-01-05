function beginEdit()
{
	var items = document.getElementsByClassName("profileInfo")
    for(var i =0; i < items.length; i++)
	{
		items[i].style.display = "none";
	}
	
	var items = document.getElementsByClassName("profileForm")
    for(var i =0; i < items.length; i++)
	{
		items[i].style.display = "block";
	}
	var items = document.getElementsByClassName("inlineInput")
    for(var i =0; i < items.length; i++)
	{
		items[i].style.display = "inline";
	}
	
}

function endEdit()
{
	var items = document.getElementsByClassName("profileInfo")
    for(var i =0; i < items.length; i++)
	{
		items[i].style.display = "block";
	}
	
	var items = document.getElementsByClassName("profileForm")
    for(var i =0; i < items.length; i++)
	{
		items[i].style.display = "none";
	}
}