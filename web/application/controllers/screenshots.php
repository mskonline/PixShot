<?php

class Screenshots extends CI_Controller {

	public function __construct() {
	
		parent::__construct();
		
	}

	function index() {
		$data['view'] = 'screenshots';
		$this->load->view('screenshots',$data);
	}
} 
?>
