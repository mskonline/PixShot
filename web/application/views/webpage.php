<!--
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title>PixShot - Home</title>
		<link href='http://fonts.googleapis.com/css?family=Amethysta' rel='stylesheet' type='text/css'>
		<link rel="stylesheet" href="./resources/css/ext-all.css">
        <link rel="stylesheet" href="./resources/css/style.css">
		
        <script src="./resources/scripts/ext-all.js" type="text/javascript"></script>

        <script>
			Ext.onReady(function(){
				Ext.each(Ext.select('#menu li a').elements,function(e, index){
					var menuElement = new Ext.Element(e);
					menuElement.on('click', menuClick,this);
				});
				
				function menuClick(evt, el, o) {
					Ext.get('content').load({
						url : el.id
					});
					evt.preventDefault();
					evt.stopPropagation();
				}
			});
        </script>
        
    </head>
	<body>
          <div id="main">
                <div id="container">
                    <div id="header">
                        <div id="logoContainer">
							Pixshot
                        </div>
                    </div> 
					<div id="menucontainer">
                                <ul id="menu">
                                        <li><a id="Home" href="#">Home</a></li>
										<li><a id="Screenshots" href="#">Screenshots</a></li>             
                                        <li><a id="Feedback" href="#">Feedback</a></li>
                                        <li><a id="Contacts" href="#">Contact</a></li>
                                </ul>
                         </div>
                    <div id="content">
                    </div> <!-- content -->
                    <!--<div id="footer">
                            <div id="copyrights">
                                <p> Copyright <?php print date('Y');  ?> All Rights Reserved. </p>
                            </div>          
                    </div>-->
                </div> <!-- container 
          </div>
    </body>
</html>-->