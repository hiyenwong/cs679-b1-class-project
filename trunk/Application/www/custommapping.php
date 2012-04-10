<?php
require_once '../includes/config.inc';
require_once 'access.inc';
require_once 'accessdeniedexception.inc';

try {
	$access = new Access();
	$access->authenticate();
	$user = $access->getUser();

	$transaction = false;
	
	if (array_key_exists('submitted', $_REQUEST) && $_REQUEST['submitted'] == 'Preview') {
		try {
			$return = array();
			
			if (($handle = fopen($_FILES['csv_file']['tmp_name'], "r")) !== FALSE) {
				$row = 0;
				while (($data = fgetcsv($handle, 1000, ",")) !== FALSE && $row < 20) {
					$row++;
					$return[] = $data;
				}
				fclose($handle);
			}
			
			echo base64_encode(json_encode(array('success' => 'yes', 'results' => $return)));
		} catch (Exception $e) {
			echo json_encode(array('success' => 'no'));
		}
		
	} else {
		$smarty = new MySmarty($SMARTY_CONFIG);
		$smarty->assign('user', $user);
		$smarty->assign('left_menu', true);
		$smarty->display('custommapping.tpl');
	}
	
} catch (AccessDeniedException $e) {
	header ('HTTP/1.1 401 Access Denied');
	echo "AccessDeniedException: " . $e->getMessage ();
} catch (Exception $e) {
	if ($transaction && !$transaction->isComplete ()) {
		$transaction->rollback ();
	}
	header ('HTTP/1.1 500 Internal Server Error');
	echo "Exception: " . $e->getMessage ();
}

?>