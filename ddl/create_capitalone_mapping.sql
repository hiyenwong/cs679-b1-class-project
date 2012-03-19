INSERT INTO mapping(name, starting_row) VALUES('CapitalOne', 2);

INSERT INTO mapping_detail
SELECT id, 'TRANSACTION_DATE', '0' FROM mapping WHERE name = 'CapitalOne';

INSERT INTO mapping_detail
SELECT id, 'NAME', '2' FROM mapping WHERE name = 'CapitalOne';

INSERT INTO mapping_detail
SELECT id, 'AMOUNT', '3' FROM mapping WHERE name = 'CapitalOne';

INSERT INTO mapping_detail
SELECT id, 'AMOUNT', '3' FROM mapping WHERE name = 'CapitalOne';