Ext.onReady(function(){
	Ext.each(Ext.select('#menu li a').elements,function(e, index){
		var menuElement = new Ext.Element(e);
		menuElement.on('click', menuClick,this);
	});
	
	function menuClick(evt, el, o) {
		this.link = el.id;
		Ext.get('content').load({
			url : el.id,
			scope: this,
			scripts : true,
			success : function(){
				if(this.link == 'feedback') {
					var panel = Ext.create('FeedbackForm',{
						renderTo : Ext.get('fbForm')
					});
					
					panel.show();
				} else  if(el.id == ''){
				
				}
			}
		});
		evt.preventDefault();
		evt.stopPropagation();
	}
	
	Ext.get('content').load({
			url : 'home',
			scripts : true
	});
});

function attachDownloadButton() {
		Ext.get('downloadButton').on('click',function(event){
	    		window.location = "./download/version/1.0";
	    });

		/*var release1 = moment([2007, 0, 29]);
		var now = moment();
		$('#release1').html(' - ' + release1.from(now));*/
}