build-apk:
	if [ ! -d "build" ]; then mkdir build; fi
	cd ./mobile-app && flutter build apk --release
	cp mobile-app/build/app/outputs/flutter-apk/app-release.apk ./build/hanalab-wheelchair.apk
