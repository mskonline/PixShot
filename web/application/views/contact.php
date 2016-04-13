<div>	
		<div class="pageHeading"> Contact </div>
		<div id="contactForm">
			<p> Name </p> <input id='nameInput' type='text'/> 
			<p> Email </p> <input id='emailInput' type='text'/> 
			<p> Details </p> <textarea id='detailsInput'> </textarea> 
			</br> </br>
			<button id="contactSubmit">Submit</button>
			<button id="contactReset">Reset</button>
			<script type="text/javascript" src="./resources/scripts/ext-base.js"></script>
			<script type="text/javascript" src="./resources/scripts/ext-all.js"></script>

			<link rel="stylesheet" type="text/css" href="./resources/css/ext-all.css"/>
			<script type="text/javascript">
			Ext.onReady(function(){

				// Creating form elements
				Ext.BLANK_IMAGE_URL = './resources/images/default/s.gif';

				var nameField = new Ext.form.TextField({
					name : 'nameField',
					applyTo: 'nameInput',
					anchor : '95%',
					blankText : 'This field is required',
					maxLength : 50,
					width : 280,
					height : 30
				});

				var emailField = new Ext.form.TextField({
					name : 'emailField',
					applyTo: 'emailInput',
					anchor : '95%',
					blankText : 'This field is required',
					maxLength : 30,
					width : 280,
					height : 30
				});

				var contactField = new Ext.form.TextArea({
					name : 'contactField',
					applyTo: 'detailsInput',
					anchor : '95%',
					blankText : 'This field is required',
					maxLength : 1000,
					width : 350,
					height : 325
				});

				var submitButton = Ext.get('contactSubmit');
				var resetButton = Ext.get('contactReset');

				submitButton.on('click', function(){

					var name = nameField.getValue();
					var email = emailField.getValue();
					var contact = contactField.getValue();

					if(name == '') {
						Ext.Msg.alert('Required','Please enter your Name');
						return;
					}

					if(email == '') {
						Ext.Msg.alert('Required','Please enter your Email. It will be kept Secret.');
						return;
					}

					if(contact == '') {
						Ext.Msg.alert('Required','Please enter any details for which you want to Contact Us');
						return;
					}

					Ext.Ajax.request({

						url: 'contact/submit',
						method: 'GET',
						params: {
							name: name,
							email: email,
							details: contact
						},
						success: function(status, response){

							var s = status.responseText;
							if(s == '1') {
								Ext.Msg.alert('Thank you','We will get back to you as soon as possible');
								nameField.setValue('');
								emailField.setValue('');
								contactField.setValue('');
							}
						}
					});
				});

				resetButton.on('click',function() {

					nameField.setValue('');
					emailField.setValue('');
					contactField.setValue('');
				})
			});
			</script>
		</div>
</div>