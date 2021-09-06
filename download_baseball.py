import boto3
import os


BASE_DIR = os.getcwd()
IMAGE_DIR = os.path.join(BASE_DIR, 'images')
AWS_ACCESS_KEY_ID = "[AKIARY7HHQEDOGECBCM6]"
AWS_SECRET_ACCESS_KEY = "[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]"
AWS_DEFAULT_REGION = "ap-northeast-2"
AWS_BUCKET_NAME = "kmyobinbaseball"

client = boto3.client('s3',
                      aws_access_key_id=AWS_ACCESS_KEY_ID,
                      aws_secret_access_key=AWS_SECRET_ACCESS_KEY,
                      region_name=AWS_DEFAULT_REGION
                      )
s3 = boto3.resource('s3')

buckets = s3.Bucket(name=AWS_BUCKET_NAME)



# S3 Client 생성
s3 = boto3.client('s3')

# S3에 있는 현재 버킷리스트의 정보를 가져온다
response = s3.list_buckets()

#print(response)

# response에 담겨있는 Buckets의 이름만 가져와 buckets 변수에 배열로 저장
buckets = [bucket['Name'] for bucket in response['Buckets']]

# S3 버킷 리스트를 출력
#print("Bucket List: %s" % buckets)


# 업로드할 파일 이름
filename = "score.dll"

# 업로드할 버킷
bucket_name = 'kmyobinbaseball'

# 첫 번째 매개변수 : 로컬에서 올릴 파일이름
# 두 번째 매개변수 : S3 버킷 이름
# 세 번째 매개변수 : 버킷에 저장될 파일 이름.
#s3.upload_file(filename, bucket_name, filename)
s3.download_file(bucket_name,filename,'score.dll')


