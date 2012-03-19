INSERT INTO mapping(name, starting_row) VALUES('Chase Credit Card', 2);

INSERT INTO mapping_detail
SELECT id, 'TRANSACTION_DATE', '1' FROM mapping WHERE name = 'Chase Credit Card';

INSERT INTO mapping_detail
SELECT id, 'NAME', '3' FROM mapping WHERE name = 'Chase Credit Card';

INSERT INTO mapping_detail
SELECT id, 'AMOUNT', '4' FROM mapping WHERE name = 'Chase Credit Card';