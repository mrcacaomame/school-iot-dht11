-- データベースを作成する
CREATE DATABASE school;

-- ユーザを作成する
CREATE USER school WITH PASSWORD 'password';

-- ユーザに権限を付与する
GRANT ALL PRIVILEGES ON DATABASE school TO school;

\c

-- テーブル設計
CREATE TABLE info (
    id          SERIAL PRIMARY KEY,
    hum         FLOAT DEFAULT NULL,
    tem         FLOAT DEFAULT NULL,
    created_at  TIMESTAMPTZ DEFAULT CURRENT_TIMESTAMP,
    del         BOOLEAN DEFAULT FALSE
);

GRANT ALL PRIVILEGES ON info TO school;
