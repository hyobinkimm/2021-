import boto3
import os

BASE_DIR = os.getcwd()
IMAGE_DIR = os.path.join(BASE_DIR, 'images')
AWS_ACCESS_KEY_ID = "[AKIARY7HHQEDOGECBCM6]"
AWS_SECRET_ACCESS_KEY = "[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]"
AWS_DEFAULT_REGION = "ap-northeast-2"
AWS_BUCKET_NAME = "kmyobincard"

client = boto3.client('s3',
    aws_access_key_id=AWS_ACCESS_KEY_ID,
    aws_secret_access_key=AWS_SECRET_ACCESS_KEY,
    region_name=AWS_DEFAULT_REGION
    )
s3 = boto3.resource('s3')

# S3 Client 생성
s3 = boto3.client('s3')

# 업로드할 파일 이름
filename = "score.dll"

# 업로드할 버킷
bucket_name = 'kmyobincard'

s3.upload_file(filename, bucket_name, filename)
