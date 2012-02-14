<?php
include_once 'database.inc';
include_once 'cache.inc';

class Transaction {

	private static $ID = 0;

	private static $STATE_BLANK = 0;
	private static $STATE_START = 1;
	private static $STATE_COMMIT = 2;
	private static $STATE_ROLLBACK = 3;

	private $id;
	private $state;
	private $cache;
	private $db;

	public function __construct (MySqlDB $db) {
		$this->id = self::$ID++;
		$this->state = self::$STATE_BLANK;
		$this->cache = Cache::getCache ();
		$this->db = $db;
	}

	public function start () {

		if ($this->state != self::$STATE_BLANK) {
			throw new Exception ('Can only start a new Transaction.');
		}

		$this->db->startTransaction();

		$this->state = self::$STATE_START;
	}

	public function commit () {

		if ($this->state != self::$STATE_START) {
			throw new Exception ('Can only commit a Transaction that has been started.');
		}

		$this->cache->writeAndFlush ();

		$this->db->commitTransaction();

		$this->state = self::$STATE_COMMIT;
	}

	public function rollback () {

		if ($this->state != self::$STATE_START) {
			throw new Exception ('Can only rollback a Transaction that has been started.');
		}

		$this->cache->flush ();

		$this->db->rollbackTransaction();

		$this->state = self::$STATE_ROLLBACK;
	}

	public function isComplete () {
		return ($this->state == self::$STATE_COMMIT || $this->state == self::$STATE_ROLLBACK);
	}

	public function __toString () {

		switch ($this->state) {
			case self::$STATE_BLANK:
				$state = 'New';
				break;
			case self::$STATE_START:
				$state = 'Started';
				break;
			case self::$STATE_COMMIT:
				$state = 'Commited';
				break;
			case self::$STATE_ROLLBACK:
				$state = 'Rolled Back';
				break;
		}

		return 'Transaction #' . $this->id . ' (' . $state . ') - ' . $this->cache;
	}
}