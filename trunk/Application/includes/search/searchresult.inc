<?php

require_once 'search/displayable.inc';
require_once 'search/exportable.inc';
require_once 'search/searchelement.inc';
require_once 'date.inc';

define ('PAGE_SIZE', 25);

class SearchResult implements Displayable, Exportable {

	private $id;

	private $size;
	private $paged;
	private $headers;
	private $rows;
	private $tooltips;
	private $sortHeader;
	private $sortOrder;
	private $url;
	private $doSort;
	private $extraUrlParams;

	public function __construct (Array $params = null) {
		$this->id = isset($params['id']) ? $params['id'] : 'sr' . rand ();
		$this->name = isset($params['name']) ? $params['name'] : 'Search Result';
		$this->size = isset($params['size']) ? $params['size'] : 0;
		$this->paged = isset($params['paged']) ? $params['paged'] : false;
		$this->headers = array ();
		$this->rows = array ();
		$this->tooltips = array ();
		$this->extraUrlParams = array ();
		$this->sortHeader = isset($params['mysortheader']) ? $params['mysortheader'] : false;
		$this->sortOrder = isset($params['mysortorder']) ? $params['mysortorder'] : "asc";
		$this->doSort = isset($params['doSort']) ? $params['doSort'] : true;
	}

	public function getId () {
		return $this->id;
	}

	public function setName ($name) {
		$this->name = $name;
	}

	public function getName () {
		return $this->name;
	}

	public function setSize ($size) {
		$this->size = $size;
	}

	public function getSize () {
		return $this->size;
	}

	public function setHeaders (Array $headers) {
		$this->headers = $headers;
	}

	public function getHeaders () {
		return $this->headers;
	}

	public function getHeaderCount () {
		return count ($this->headers);
	}

	public function setRows (Array $rows) {
		$this->rows = $rows;
	}

	public function setPaged ($paged) {
		$this->paged = $paged;
	}

	public function getRows () {
		if ($this->doSort) {
			$this->sort();
		}
		return $this->rows;
	}

	public function sort() {
		// Do not sort unless it is told to do so
		if ($this->sortHeader) {
			if ($this->rows[0][$this->sortHeader] instanceof Date) {
				usort($this->rows, array($this, "sortDatel"));
			} else if ($this->rows[0][$this->sortHeader] instanceof SearchElement) {
				usort($this->rows, array($this, "sortSearchElementl"));
			} else {
				usort($this->rows, array($this, "sortStringl"));
			}
		}
	}

	public function setDoSort($doSort = true) {
		$this->doSort = $doSort;
	}

	public function getDoSort() {
		return $this->doSort;
	}

	private function sortStringl ($a, $b) {
		return SearchResult::sortString($a["$this->sortHeader"], $b["$this->sortHeader"], $this->sortOrder);
	}

	public static function sortString ($a, $b, $sortOrder) {
		if ($sortOrder != "asc" && $sortOrder != "desc") {
			return 0;
		}

		if (!isset($a)) {
			return ($sortOrder == "asc") ? -1 : 1;
		} else if (!$b) {
			return ($sortOrder == "asc") ? 1 : -1;
		} else if (strtolower((string) $a) == strtolower((string) $b)) {
			return 0;
		} else {
			if ($sortOrder == "asc") {
				return (strtolower((string) $a) > strtolower((string) $b)) ? 1 : -1;
			} else {
				return (strtolower((string) $a) < strtolower((string) $b)) ? 1 : -1;
			}
		}

	}


	private function sortSearchElementl($a, $b) {
		return SearchResult::sortSearchElement($a["$this->sortHeader"], $b["$this->sortHeader"], $this->sortOrder);
	}

	public static function sortSearchElement($a, $b, $sortOrder) {
		if ($sortOrder != "asc" && $sortOrder != "desc") {
			return 0;
		}

		// Incase of Date object within search element
		if ($a->getName() instanceof Date) {
			return SearchResult::sortDate($a->getName(), $b->getName(), $sortOrder);
		} else {
			if (!isset($a)) {
				return ($sortOrder == "asc") ? -1 : 1;
			} else if (!isset($b)) {
				return ($sortOrder == "asc") ? 1 : -1;
			} else if (strtolower($a->getName()) == strtolower($b->getName())) {
				return 0;
			} else {
				if ($sortOrder == "asc") {
					return (strtolower($a->getName()) > strtolower($b->getName())) ? -1 : 1;
				} else {
					// Second Condition is guarentee to be desc because of the first if
					return (strtolower($a->getName()) < strtolower($b->getName())) ? -1 : 1;
				}
			}

		}


	}


	private function sortDatel($a, $b) {
		return SearchResult::sortDate($a["$this->sortHeader"], $b["$this->sortHeader"], $this->sortOrder);
	}

	public static function sortDate($a, $b, $sortOrder) {
		if ($sortOrder != "asc" && $sortOrder != "desc") {
			return 0;
		}

		if (!isset($a)) {
			return ($sortOrder == "asc") ? -1 : 1;
		} else if (!isset($b)) {
			return ($sortOrder == "asc") ? 1 : -1;
		} else if ($a->equals($b)) {
			return 0;
		} else {
			if ($sortOrder == "asc") {
				return ($a->earlierThan($b)) ? -1 : 1;
			} else {
				// Second Condition is guarentee to be desc because of the first if
				return ($a->laterThan($b)) ? -1 : 1;
			}
		}

	}



	public function getSortHeader() {
		return $this->sortHeader;
	}

	public function setSortHeader($sortHeader) {
		$this->sortHeader = $sortHeader;
	}

	public function getSortOrder() {
		return $this->sortOrder;
	}

	public function setSortOrder($sortOrder) {
		$this->sortOrder = $sortOrder;
	}

	public function getRowCount () {
		return count ($this->rows);
	}

	public function getPage ($pageNumber) {

		$rows = $this->getRows();

		if (!$this->paged) {
			return $rows;
		}

		if (!is_numeric ($pageNumber) || !$pageNumber) {
			throw new Exception ('Page Number must be a real integer.');
		}

		$pagedRows = array ();

		$start = ($pageNumber - 1) * PAGE_SIZE;
		$end = $start + PAGE_SIZE;

		for ($i = $start; $i < $end; $i++) {
			$pagedRows [] = $rows [$i];
		}

		return $pagedRows;
	}

	public function getPageCount () {

		if (!$this->paged) {
			return 1;
		}

		return ceil (count ($this->rows) / PAGE_SIZE);
	}

	public function addRow (Array $row) {
		$this->rows [] = $row;
	}

	public function isPaged () {
		return ($this->paged);
	}

	public function hasTooltips () {
		return (count ($tooltips));
	}

	public function getTooltips () {
		return $this->tooltips;
	}

	public function getUrl() {
		$arr = explode("?",$_SERVER['REQUEST_URI']);

		$myurl = $arr[0] . "?";
		$arr = explode("&",$arr[1]);
		$counter = 0;
		foreach ($arr AS $val) {
			$pair = explode("=", $val);
			if ($pair[0] != "mysortheader" && $pair[0] != "mysortorder" && $pair[0] != "paged"
					&& !array_key_exists($pair[0], $this->extraUrlParams)) {
				if ($counter > 0) {
					$myurl .= "&";
				}
				$myurl .= $val;
				$counter++;
			}
		}

		foreach ($this->extraUrlParams as $key=>$value) {
			if ($counter > 0) {
				$myurl .= "&";
			}
			$myurl .= $key . "=" . $value;
		}

		return $myurl;
	}

	public function appendToUrl($key, $value) {
		$this->extraUrlParams[$key] = $value;
	}


	public function setTooltips (Array $tooltips) {
		$this->tooltips = $tooltips;
	}

	/************************* Iterator Implementation	*************************/

	public function rewind () {
		reset ($this->rows);
	}

	public function current () {
		$row = current ($this->rows);
		return $row;
	}

	public function key () {
		$key = key ($this->rows);
		return $key;
	}

	public function next () {
		$row = next ($this->rows);
		return $row;
	}

	public function valid () {
		$row = current ($this->rows);
		return ($row !== false);
	}

	public function __toString () {
		return $this->getName ();
	}

	/************************* Exportable Implementation	*************************/

	public function export (Smarty $smarty = null) {

		if (!$this->getRows ()) {
			throw new Exception ('There is no data in this search result to export.');
		}

		if (headers_sent ()) {
			throw new Exception ('Headers already sent, could not export this search result.');
		}

		if ($smarty) {
			$system_url = $smarty->get_template_vars ('system_url');
			$redirect_url = $smarty->get_template_vars ('redirect_url');
			$text = (isset ($_COOKIE ['exporttext']) && ($_COOKIE ['exporttext'] == 1));

			$smarty->clear_all_cache ();
			$smarty->clear_all_assign ();
			ob_end_clean ();
		}

		$fp = fopen ('php://output', 'w');

		header ('Content-Type: application/vnd.ms-excel');
		header ('Content-Disposition: attachment; filename="' . $this->__toString () . ' (' . strftime ('%m-%d-%Y') . ').csv"');

		$headers = $this->getHeaders ();

		fputcsv ($fp, $headers);

		foreach ($this as $row) {
			$line = array ();

			foreach ($headers as $header) {

	if (is_a ($row [$header], 'SearchElement')) {

		if ($smarty && $row [$header]->getLink () && !$text) {
			$line [] = '=HYPERLINK("' . $system_url . $redirect_url . '?ref=' . base64_encode ($row [$header]->getLink ()) . '", "' . $row [$header]->getName () . '")';

		} else {
			$line [] = $row [$header]->getName ();
		}

	} else if (is_array ($row [$header])) {
		$line [] = implode ($row [$header], '; ');

	} else {
		$line [] = $row [$header];
	}
			}

			fputcsv ($fp, $line);
		}

		fclose ($fp);
		exit ();
	}

	public function getNonPagedLink () {
		$qs = false;

		if ($_SERVER ['QUERY_STRING']) {
			$qs = preg_replace ('/&?page=\d+/', '', $_SERVER ['QUERY_STRING']);
		}

		return $qs;
	}
}
?>