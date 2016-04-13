<?php

class Feedback extends CI_Controller {

	public function __construct() {
	
		parent::__construct();
		$this->load->model('DBManager');
		
	}

	function index() {
		$this->load->view('feedback');
	}

	function submit($name = 'name', $email = 'email', $feedback = 'feedback') {

		$name = $_GET['name'];
		$email = $_GET['email'];
		$details = $_GET['feedback'];

		echo $this->DBManager->saveFeedBack($name,$email,$details);
	}
} 
?>