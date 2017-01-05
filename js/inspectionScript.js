function editInspection(index)
{
	window.scrollTo(0, 0);
	document.getElementById("createButton").style='display: none'
	document.getElementById("updateButton").style='display: inline !important'
	document.getElementById("deleteButton").style='display: inline !important'
	
	var inspection = document.getElementById("plannedInspections").rows[index].cells;
	var date = inspection[1].innerHTML;
	var details = inspection[4].innerHTML;
	var houseID = inspection[5].innerHTML;
	var inspectionID = inspection[6].innerHTML;
	
	document.getElementById("houseID").value = houseID;
	document.getElementById("details").value = details;
	document.getElementById("date").value = date;
	document.getElementById("inspectionID").value = inspectionID;
}