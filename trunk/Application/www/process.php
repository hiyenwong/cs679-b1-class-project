<?php
require_once '../includes/config.inc';
require_once 'access.inc';
require_once 'accessdeniedexception.inc';
require_once 'user.inc';
require_once 'activity.inc';
require_once 'mapping.inc';
require_once 'date.inc';
require_once 'factory.inc';
require_once 'view.inc';
require_once 'transaction.inc';

try {
// 	$access = new Access();
// 	$access->authenticate();
// 	$user = $access->getUser();

	$user = Factory::getView(new UserKey('3'));

	$transaction = false;
	
	if (!empty($_POST)) {
		if (!array_key_exists('csv_file', $_FILES)) {
			throw new Exception("Missing required parameter: file");
		}
		
		if (!array_key_exists('mapping_type', $_REQUEST)) {
			throw new Exception("Missing required parameter: mapping type");
		} else {
			$mapping_key = htmlentities($_REQUEST['mapping_type']);
		}

		$transaction = new Transaction(new MySqlDB());
		$transaction->start();
		
		$mapping = Factory::getView(new MappingKey($mapping_key));
		
		$tmpname = $_FILES['csv_file']['tmp_name'];
		if (($handle = fopen($tmpname, "r")) !== FALSE) {
			$row = 0;
			while (($data = fgetcsv($handle, 1000, ",")) !== FALSE) {
				$row++;
				if ($row < $mapping->getStartingRow()) {
					// Getting to starting row;
					continue;
				}

				$activity = Factory::createView(new ActivityKey());
				$activity->setUser($user);
				foreach ($mapping->getMappingDetails() as $map) {
					switch ($map->getColumnName()) {
						case MappingDetail::$MAPPING_TRANSACTION_DATE:
							$activity->setTransactionDate(new Date($data[$map->getCsvColumnNumber()]));
							break;
						case MappingDetail::$MAPPING_AMOUNT:
							$activity->setAmount($data[$map->getCsvColumnNumber()]);
							break;
						case MappingDetail::$MAPPING_NAME:
							$activity->setName($data[$map->getCsvColumnNumber()]);
							break;
					}
				}
			}
			fclose($handle);
		}
		
		$transaction->commit();
		
		echo "Finish";
		
	} else {
		$smarty = new MySmarty($SMARTY_CONFIG);
		$smarty->assign('mappingTypes', Mapping::getOptions());
		$smarty->display('process.tpl');
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