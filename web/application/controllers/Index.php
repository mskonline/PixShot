<?php

class Index extends CI_Controller {

	public function __construct() {
	
		parent::__construct();
		$this->load->model('Dbmanager');
	}

	function index() {
		$this->load->view('index');
	}
} 
?>
