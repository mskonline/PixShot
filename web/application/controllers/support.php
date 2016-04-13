<?php

class Support extends CI_Controller {

	public function __construct() {
	
		parent::__construct();
		
	}

	function index() {
	
		$data['view'] = 'support';
		$this->load->view('webpage',$data);
	}

} 
?>