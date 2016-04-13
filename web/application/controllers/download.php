<?php

class Download extends CI_Controller {

	public function __construct() {
	
		parent::__construct();
		$this->load->model('DBManager');
		$this->load->helper('download');
	}

	function index() {
	
		$data['view'] = 'download';
		$this->load->view('webpage',$data);
	}

	function version($version = '1.0',$type = 'win_exe', $fileName = 'Setup.exe') {

		$filePath = "./data/".$version."/".$type."/".$fileName;
		$data = "";

		try {
			$data = file_get_contents("".$filePath);
			$this->DBManager->incrementDownloadCount($version);

			force_download($fileName,$data);
		} catch(Exception $exp) {
			log_message('error',$exp->getMessage());
		}	
	}
} 
?>
