// Check off Specific Todos By Clicking
$("ul").on("click", "li", function(){ 
	// added to ul parent, because that exists when the page loads
	// this way we can make changes to the li's that don't exist yet
	$(this).toggleClass("completed");	
})

// Click on X to delete Todo
$("ul").on("click", "span", function(event){
	$(this).parent().fadeOut(500, function(){
		//when the fadeout is doen, remove the li
		$(this).remove(); //refers to the parent element (li)
	})
	event.stopPropogation(); //this will stop all other actions from running on the element
})

// 
$("input[type='text']").keypress(function(event){
	//check that the key was enter
	if(event.which === 13){
		// grab text from input
		var todoText = $(this).val();

		//clear the input field
		$(this).val("");

		//create new li and add to ul
		$("ul").append("<li><span><i class='fa fa-trash'></i></span> " + todoText + "</li>")
	}
});

$(".fa-plus-circle").click(function(){
	$("input[type='text']").fadeToggle();
});