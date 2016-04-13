<?php

class Index extends CI_Controller {

	public function __construct() {
	
		parent::__construct();
		$this->load->model('DBManager');
	}

	function index() {
		$data['cVersionRecord'] = $this->DBManager->currenVersionDownloadCount();
		$this->load->view('index',$data);
	}
} 
?>
