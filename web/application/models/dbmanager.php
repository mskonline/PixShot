<?php 

class Dbmanager extends CI_MODEL {
	
	var $currentVersion  = "0.9";

	public function __construct() {
	
		parent::__construct();
		$this->load->database();
		$this->load->helper('date');
	}
	
	public function incrementDownloadCount($version) {
	
		$db = $this->db;
		try {
			$db->where('version',$version);
			$db->from('downloads');
			$query = $db->get();
			$record = $query->result_array();

			//print_r($record);
			
			$record[0]['totaldownloads'] = $record[0]['totaldownloads'] + 1;
			
			$datestring = "%Y-%m-%d";
			$now = now();
			
			$timestamp = 'UP45';
			$dayLightSaving = 'TRUE';
			$dt = gmt_to_local($now,$timestamp,$dayLightSaving);
			//echo mdate($datestring, $dt);
			
			$record[0]['lastdownloaded'] = mdate($datestring, $dt);
			
			$db->where('version',$version);
			$db->update('downloads',$record[0]);

			//print_r($record);
		} catch (Exception $exp) {
			log_message('error','Error while incrementing count');
			log_message('error',$exp->getMessage());
		}
	}
	
	public function currenVersionDownloadCount() {
	
		try {

			$db = $this->db;
			$db->select('totaldownloads');
			$db->where('version', $this->currentVersion);
			$db->from('downloads');
			$query = $db->get();

			if(!$query)
				throw new Exception('error in retrieving count');
			else
			{
				return $query->result_array();
			}
				
		} catch (Exception $exp) {
			log_message('error',$exp->getMessage());
			//TODO : return empty array
			return '-';
		} 
	}
	
	public function saveFeedBack($name, $email, $feedback) {

		$db = $this->db;

		$data = array(
			'name' => $name,
			'email' => $email,
			'feedback' => $feedback
			);

		return $db->insert('feedback',$data);
	}

	public function saveContactDetails($name, $email, $details) {

		$db = $this->db;

		$data = array(
			'name' => $name,
			'email' => $email,
			'details' => $details
			);

		return $db->insert('contact',$data);
	}

	/*public function populateHomeContent() {
	
			$db = $this->db;
			$db->select('title,publish_date,short_summary');
			$db->order_by('publish_date','desc');
			$db->from('articles');
			//$this->db->limit(10);
			
			$query = $db->get();
			return $query->result_array();
	}
	
	public function populateRecentArticles() {
		
			$db = $this->db;
			$db->select('title');
			$db->order_by('publish_date','desc');
			$db->from('articles');
			
			$query = $db->get();
			return $query->result_array();
	}
	
	public function loadArticle($articleXml) {
	
			$db = $this->db;
			$db->set('id',$articleXml->id);
			$db->set('type',"'".$articleXml->type."'",FALSE);
			$db->set('title',"'".$articleXml->title."'",FALSE);
			$db->set('short_summary',"'".$articleXml->short_summary."'",FALSE);
			$db->set('content',"'".$articleXml->content."'",FALSE);
			$db->set('publish_date',"'".$articleXml->publish_date."'",FALSE);
			$db->insert('articles');
	} */
}
?>