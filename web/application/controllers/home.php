<?php

class Home extends CI_Controller {

	public function __construct() {
	
		parent::__construct();
		$this->load->model('DBManager');
	}

	function index() {
		$data['view'] = 'home';
		$data['cVersionRecord'] = $this->DBManager->currenVersionDownloadCount();
		$this->load->view('home',$data);
	}
} 
?>
