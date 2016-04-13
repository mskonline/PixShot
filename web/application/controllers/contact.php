<?php

class Contact extends CI_Controller {

	public function __construct() {
	
		parent::__construct();
		$this->load->model('DBManager');
	}

	function index() {
		$this->load->view('contact',$data);
	}

	function submit($name = 'name', $email = 'email', $details = 'details') {

		$name = $_GET['name'];
		$email = $_GET['email'];
		$details = $_GET['details'];

		echo $this->DBManager->saveContactDetails($name,$email,$details);
	}
} 
?>