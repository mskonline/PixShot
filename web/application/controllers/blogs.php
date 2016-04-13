<?php

class Blogs extends CI_Controller {

	public $type = 'blog';

	public function __construct() {
		
		parent::__construct();
		$this->load->model('Articles');
	}

	function index() {
		
		/*$data['Blogs'] = $this->Articles->getAllBlogs() ;
		$this->load->view('Blogs', $data);
		
		$this->load->view('Header');
		$this->load->view('Blogs', $data);
		$this->load->view('Footer');*/
	}

	function main() {
		
		$data['Blogs'] = $this->Articles->getAllBlogs() ;
		$this->load->view('Blogs', $data);
	}
	
	function post($postTitle = '') {
	
		if($postTitle != null)
			$title =  urldecode($postTitle);
		else
		{
			$this->load->view('Home');
			return;
		}
		
		$data['postContent'] = $this->Articles->getArticleDetails($this->type, $title);
		
		//$this->load->view('Home2');
		$this->load->view('postContent',$data);
	}
} 
?>